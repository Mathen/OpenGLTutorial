#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "Debug.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "Mesh.h"
#include "Fractal.h"
#include "CubeFractal.h"
#include "TriangleFractal.h"
#include "SphereFractal.h"

void Tutorial();
void FractalSim();

int main()
{
    //Tutorial();
    FractalSim();
}

void FractalSim()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Fractal", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); //V-Sync

    if (glewInit() != GLEW_OK)
        std::cout << "Error: glewInit() should go after glfwMakeContextCurrent()" << std::endl;

    std::cout << "Driver Version: " << glGetString(GL_VERSION) << std::endl;

    //GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //GlCall(glEnable(GL_BLEND));

    Shader* rainbowShader = new Shader("res/shaders/Rainbow.shader");
    Shader* outlineShader = new Shader("res/shaders/OutlineBlack.shader");
    

    Fractal* fractal = nullptr;
    std::cout << "Enter shape (1, 2, 3):" << std::endl;
    int i;
    std::cin >> i;
    if (i == 1)
    {
        fractal = new SphereFractal(rainbowShader);
        std::cout << "Selected Sphere\n";
    }
    else if (i == 2)
    {
        fractal = new TriangleFractal(rainbowShader);
        std::cout << "Selected Triangle\n";
    }
    else if (i == 3)
    {
        fractal = new CubeFractal(rainbowShader);
        std::cout << "Selected Cube\n";
    }
    else
    {
        std::cout << "Not valid shape" << std::endl;
        return;
    }

    bool outline;
    char temp;
    std::cout << "Show Edges (Y/N):\n";
    std::cin >> temp;
    outline = temp == 'Y';

    //Matrix stuff
    //Cube
    glm::mat4 mvp = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    //*
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    //glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

    glm::vec3 cameraPosition(3, 4, 4);
    glm::mat4 view = glm::lookAt(
        cameraPosition, // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 model = glm::mat4(1.0f); //Object at origin
    mvp = projection * view * model;
    //*/
    rainbowShader->SetUniform4f("MVP", mvp);
    outlineShader->SetUniform4f("MVP", mvp);

    Renderer renderer;

    //Game Loop
    bool space = false;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        renderer.DrawTriangles(*fractal);
        if (outline)
            renderer.DrawTrianglesOutline(*fractal, *outlineShader);

        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !space)
        {
            fractal->Divide();
            space = true;
        }
        if (glfwGetKey(window, GLFW_KEY_ENTER) != GLFW_PRESS)
        {
            space = false;
        }

        float speed = 10.0f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cameraPosition.x += -0.01f * speed;
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cameraPosition.x += 0.01f * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cameraPosition.y += -0.01f * speed;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cameraPosition.y += 0.01f * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            cameraPosition.z += -0.01f * speed;
        }
        else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            cameraPosition.z += 0.01f * speed;
        }

        view = glm::lookAt(
            cameraPosition, // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
        mvp = projection * view * model;
        rainbowShader->SetUniform4f("MVP", mvp);
        outlineShader->SetUniform4f("MVP", mvp);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete fractal;
    delete outlineShader;
    glfwTerminate();
    return;
}

void Tutorial()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Tutorial", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); //V-Sync

    if (glewInit() != GLEW_OK)
        std::cout << "Error: glewInit() should go after glfwMakeContextCurrent()" << std::endl;

    std::cout << "Driver Version: " << glGetString(GL_VERSION) << std::endl;

    float pos[] =
    {
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,    1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 1.0f,
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
    };

    //GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //GlCall(glEnable(GL_BLEND));

    VertexArray va;
    VertexBuffer vb(pos, sizeof(pos));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indicies, sizeof(indicies) / sizeof(indicies[0]));

    //Shader creation
    //Shader shader("res/shaders/Rainbow.shader");
    Shader shader("res/shaders/Texture.shader");
    shader.Bind();

    //Texture creation
    Texture texture("res/textures/landscapeFinal1.png");
    texture.Bind();
    shader.SetUniform1i("uTexture", 0);

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
    shader.SetUniform4f("MVP", mvp);

    Renderer renderer;

    //Game Loop
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        renderer.DrawTriangles(va, ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}