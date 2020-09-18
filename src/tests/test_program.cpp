#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "GLbuffer.hpp"
#include "GLshader.hpp"
#include "GLprogram.hpp"
#include "GLattrib.hpp"

using namespace std;

int test_program() {

    #pragma region GLFW_INIT

    if(!glfwInit()) {
        cout << "Fail to init GLFW!";
        getchar();
        return -1;
    }

    auto window = glfwCreateWindow(640, 480, "My Window", nullptr, nullptr);
    if(window == nullptr) {
        cout << "Fail to create WINDOW!";
        glfwTerminate();
        getchar();
        return -1;
    }

    #pragma endregion GLFW_INIT

    glfwMakeContextCurrent(window);

    #pragma region GLEW_INIT

    if(glewInit() != GLEW_OK) {
        cout << "Fail to init GLEW!";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    #pragma endregion GLEW_INIT

    glClearColor(0.5f, 1.0f, 0.5f, 1.0f);

    #pragma region DRAW_DATA

    // Shape vertices
    const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0,
         0.5f,  0.5f, 0.0,

         0.5f, -0.5f, 0.0,
        -0.5f,  0.5f, 0.0,
    };

    const GLuint indices[] = {
        0, 1, 2,
        0, 1, 3,
    };

    auto vbo = new GLbuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vbo->Bind();
    vbo->Data(sizeof(vertices), vertices);

    auto ebo = new GLbuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    ebo->Bind();
    ebo->Data(sizeof(indices), indices);

    #pragma endregion DRAW_DATA

    auto shader = new GLprogram("vert0.glsl", "frag0.glsl");
    cout << shader->GetLog();

    GLattrib attrib(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        attrib.Enable();
        vbo->Bind();
        attrib.Use();
        ebo->Bind();        
        shader->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        attrib.Disable();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete vbo;
    delete ebo;
    delete shader;
    glfwTerminate();
    return 0;
}