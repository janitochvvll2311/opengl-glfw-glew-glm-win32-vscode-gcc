#include <iostream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "GLbuffer.hpp"

using namespace std;

int test_ebo() {

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

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        glEnableVertexAttribArray(0);
        vbo->Bind();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        ebo->Bind();        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete vbo;
    delete ebo;
    glfwTerminate();
    return 0;
}