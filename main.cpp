#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

void initialize_test_image(GLuint& texture, int& image_width, int& image_height) {
    int width, height, nrChannels;
    //const char* image_path = "assets/big_demon_run_anim_f3.png";
    //const char* image_path = "assets/big_demon_run_anim_f3.bmp";
    const char* image_path = "assets/first_spell.png";
    unsigned char* data = stbi_load(image_path, &width, &height, &nrChannels, 0);
    printf("loading image: %s with width %d and height %d and channels %d\n", image_path, width, height, nrChannels);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data)
    {
        if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            std::cout << "Unsupported channel count: " << nrChannels << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

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
    GLuint texture;
    int image_width, image_height;
    initialize_test_image(texture, image_width, image_height);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


        glLoadIdentity();  // Reset the MODELVIEW matrix
        float centerX = SCREEN_WIDTH * 1.0f / 2.0f;
        float centerY = SCREEN_HEIGHT * 1.0f / 2.0f;

        glTranslatef(centerX, centerY, 0.0f);   // Move to the center of the image
        glRotatef(180.0f, 0.0f, 0.0f, 1.0f);   // Rotate around Z-axis
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);   // Rotate around Y-axis
        glTranslatef(-centerX, -centerY, 0.0f); // Move back

        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, SCREEN_HEIGHT * 1.0f / 2.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(SCREEN_WIDTH * 1.0f / 2.0f, SCREEN_HEIGHT * 1.0f / 2.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(SCREEN_WIDTH * 1.0f / 2.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
