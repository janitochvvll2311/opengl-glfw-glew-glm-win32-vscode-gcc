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
#include "Bmp.hpp"
#include "GLparameter.hpp"
#include "GLtexture.hpp"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

using namespace std;
using namespace glm;

int main() {

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
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
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

    auto ebo = new GLbuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    ebo->Bind();
    ebo->Data(sizeof(indices), indices);

    #pragma endregion DRAW_DATA

    #pragma region SHADER_CONFIG

    auto shader = new GLprogram("vert0.glsl", "frag0.glsl");
    cout << shader->GetLog();

    GLattrib aVertices(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    GLattrib aColores(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    aVertices.location = shader->GetLocation("vPosition");
    aColores.location = shader->GetLocation("vTex");

    auto vao = new GLarray();
    vao->Bind();

    vVertices->Bind();
    aVertices.Enable();
    aVertices.Use();

    vColores->Bind();
    aColores.Enable();
    aColores.Use();

    #pragma endregion SHADER_CONFIG

    #pragma region TEXTURING

    Bmp image("example.bmp");

    glEnable(GL_TEXTURE_2D);

    auto texture = new GLtexture(GL_TEXTURE_2D, 0, GL_RGB);
    texture->Bind();
    texture->Source2D(image.Width(), image.Height(), 0, GL_BGR, GL_UNSIGNED_BYTE, image.Handle());

    GLparameter wrapS(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLparameter wrapT(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLparameter mag(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLparameter min(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    wrapS.Use();
    wrapT.Use();
    mag.Use();
    min.Use();

    texture->GenerateMipmap();

    #pragma endregion TEXTURING

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    #pragma region MODELING

    mat4 mTranslation = identity<mat4>();
    mat4 mScale = identity<mat4>();

    mat4 mRotation = rotate(-45.0f, vec3(1.0f, 0.0f, 0.0f));
    mRotation = mRotation * rotate(-45.0f, vec3(0.0f, 1.0f, 0.0f));

    mat4 model = mTranslation * mRotation * mScale;

    int width;
    int height;

    glfwGetWindowSize(window, &width, &height);

    mat4 projection = perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    mat4 view = lookAt(
        vec3(0, 0, 3), // Camera is at (4,3,3), in World Space
        vec3(0, 0, 0), // and looks at the origin
        vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    mat4 MVP = projection * view * model;

    shader->Use();
    shader->SetUniformMat4("MVP", 1, GL_FALSE, &MVP[0][0]);

    #pragma endregion MODELING

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw
        vao->Bind();
        ebo->Bind();        
        shader->Use();
        //shader->SetUniformMat4("MVP", 1, GL_FALSE, &MVP[0][0]);
        texture->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete vVertices;
    delete ebo;
    delete shader;
    delete vao;
    delete texture;
    glfwTerminate();
    return 0;
}