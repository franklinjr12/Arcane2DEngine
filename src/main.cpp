#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Image.hpp"
#include "FrameController.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768



static void glfw_error_callback(int error, const char* description) {
    std::cout << "GLFW Error: " << description << std::endl;
}

int main()
{
    std::cout << "Hello World!\n";

    GLFWwindow* window;

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Set up the orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enable 2D texturing
    glEnable(GL_TEXTURE_2D);
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Image img("assets/big_demon_run_anim_f3.png");

    const int max_fps = 30;
    FramesController fc(max_fps);
    while (!glfwWindowShouldClose(window))
    {
        fc.frameBegin();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        img.draw(0, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
        fc.frameEnd();
        fc.sleep();
        std::cout << "Fps: " << fc.sleep_time << " Real Fps: " << fc.real_fps << std::endl;
    }

    glfwTerminate();
    return 0;
}
