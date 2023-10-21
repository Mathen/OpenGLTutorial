#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderSource
{
    std::string vertexSrc;
    std::string fragmentSrc;
};

static ShaderSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        delete[] message;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error: glewInit() should go after glfwMakeContextCurrent()" << std::endl;

    std::cout << "Driver Version: " << glGetString(GL_VERSION) << std::endl;

    float pos[] = 
    { 
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,

         0.0f,  0.0f,  1.2f,
         0.0f,  0.0f, -1.2f,
         0.0f,  1.1f,  0.0f,
    };
    float colors[] =
    {
        0, 0, 0,
        0, 0, 1,
        0, 1, 0,
        0, 1, 1,
        1, 0, 0,
        1, 0, 1,
        1, 1, 0,
        1, 1, 1,

        0.26f, 0.81f, 0.63f,
        0.26f, 0.81f, 0.63f,
        0.26f, 0.81f, 0.63f,
    };
    unsigned int indicies[]
    {
        0, 1, 2,
        1, 2, 3,
        0, 1, 5,
        5, 4, 0,
        1, 3, 7,
        1, 5, 7,
        3, 2, 7,
        7, 6, 2,
        2, 0, 6,
        0, 4, 6,
        5, 4, 6,
        7, 5, 6,

        8, 9, 10,
    };

    //Position transfer
    unsigned int posBuffer[1];
    glGenBuffers(1, posBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, posBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, (8 + 3) * 3 * sizeof(float), pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    //Index buffer object transfer
    unsigned int iboBuffer[2];
    glGenBuffers(1, iboBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (12 + 1) * 3 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

    //Color transfer
    unsigned int colorBuffer[2];
    glGenBuffers(1, colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, (8 + 3) * 3 * sizeof(float), colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);


    //Shader creation
    ShaderSource shaderSrc = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(shaderSrc.vertexSrc, shaderSrc.fragmentSrc);
    glUseProgram(shader);
    

    //Matrix stuff
    //Cube
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    //glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(3, 4, 4), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 model = glm::mat4(1.0f); //Object at origin
    glm::mat4 mvp = projection * view * model;
    unsigned int matrixId = glGetUniformLocation(shader, "MVP1");
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

    //Triange
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
    mvp = projection * view * model;
    matrixId = glGetUniformLocation(shader, "MVP2");
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
    
    //Depth stuff
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Game Loop
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, (12 + 1) * 3, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}