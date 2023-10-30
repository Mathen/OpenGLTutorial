#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); //V-Sync

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

    VertexArray va;
    VertexBuffer vb(pos, sizeof(pos));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indicies, sizeof(indicies) / sizeof(indicies[0]));

    //Shader creation
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

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
    shader.SetUniform4f("MVP1", mvp);

    //Triange
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
    mvp = projection * view * model;
    shader.SetUniform4f("MVP2", mvp);
    
    //Depth stuff
    GlCall(glEnable(GL_DEPTH_TEST));
    GlCall(glDepthFunc(GL_LESS));

    //Game Loop
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GlCall(glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GlCall(glDrawElements(GL_TRIANGLES, (12 + 1) * 3, GL_UNSIGNED_INT, nullptr)));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}