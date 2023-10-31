#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

class Image {
public:
    Image(std::string path) {
        loadImage(path);

    }
    void loadImage(std::string path) {
        if (texture_id != 0)
            glDeleteTextures(1, &texture_id);
        this->path = path;
        int nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        glGenTextures(1, &this->texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

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
                std::cerr << "Unsupported channel count: " << nrChannels << std::endl;
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);

    }
    void draw(float x =  -1, float y = -1) {
        if (x < 0 || y < -1) return;
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, height * 1.0f + y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width * 1.0f, height * 1.0f + y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width * 1.0f, y);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
        glEnd();
    }
    std::string path;
    int width, height;
    GLuint texture_id = 0;
};

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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        img.draw(0, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
