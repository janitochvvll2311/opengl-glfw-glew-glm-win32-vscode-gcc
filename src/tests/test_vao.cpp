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
#include "GLarray.hpp"

using namespace std;

int test_vao() {

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

    const GLfloat colores[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    const GLfloat cx[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 
    };

    const GLuint indices[] = {
        0, 1, 2,
        0, 1, 3,
    };

    auto vVertices = new GLbuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vVertices->Bind();
    vVertices->Data(sizeof(vertices), vertices);

    auto vColores = new GLbuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vColores->Bind();
    vColores->Data(sizeof(colores), colores);

    auto vCx = new GLbuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vCx->Bind();
    vCx->Data(sizeof(cx), cx);

    auto ebo = new GLbuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    ebo->Bind();
    ebo->Data(sizeof(indices), indices);

    #pragma endregion DRAW_DATA

    auto shader = new GLprogram("vert0.glsl", "frag0.glsl");
    cout << shader->GetLog();

    GLattrib aVertices(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    GLattrib aColores(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    aVertices.location = shader->GetLocation("vPosition");
    aColores.location = shader->GetLocation("vColor");

    GLattrib aCx(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    aCx.location = shader->GetLocation("vColor");

    auto vao = new GLarray();
    vao->Bind();

    vVertices->Bind();
    aVertices.Enable();
    aVertices.Use();

    vColores->Bind();
    aColores.Enable();
    aColores.Use();

    auto vx = new GLarray();
    vx->Bind();

    vVertices->Bind();
    aVertices.Enable();
    aVertices.Use();

    vCx->Bind();
    aCx.Enable();
    aCx.Use();

    GLarray *first = vao;
    GLarray *second = vx;

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        first->Bind();
        ebo->Bind();        
        shader->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        second->Bind();
        ebo->Bind();        
        shader->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if(first == vao) {
            second = vao;
            first = vx;
        }
        else {
            second = vx;
            first = vao;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete vVertices;
    delete ebo;
    delete shader;
    delete vao;

    delete vCx;
    delete vx;

    glfwTerminate();
    return 0;
}