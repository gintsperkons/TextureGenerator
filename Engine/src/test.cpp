#include <iostream>
#include "test.h"
#include <GLFW/glfw3.h>

void sayHello() {
    std::cout << "Hello, Strange World!" << std::endl;
    GLFWwindow* window;

    if (!glfwInit())
        exit(EXIT_FAILURE);


    window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }


    glfwMakeContextCurrent(window);


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}