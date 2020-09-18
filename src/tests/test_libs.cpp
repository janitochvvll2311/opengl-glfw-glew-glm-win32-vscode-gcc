#include <iostream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

int test_libs() {

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

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}