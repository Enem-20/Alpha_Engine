#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/vec2.hpp>
#include<glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"

#include <iostream>

GLfloat points[] =
{
    0.0f, 50.0f, 0.0f,
    50.0f, -50.0f, 0.0f,
    -50.0f, -50.0f, 0.0f
};

GLfloat colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat texCoord[] =
{
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}
glm::ivec2 MainWindow_size(640, 480);
//int MainWindow_sizeX = 640;
//int MainWindow_sizeY = 480;

void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
    MainWindow_size.x = width;
    MainWindow_size.y = height;

    glViewport(0, 0, MainWindow_size.x, MainWindow_size.y);
}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char** argv)
{
    
    /* Initialize the library */
    glfwSetErrorCallback(&glfwError);
    if (!glfwInit())
    {
        std::cout << "GLFW is not initialized!" << std::endl;
        system("pause");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* Mainwindow = glfwCreateWindow(MainWindow_size.x, MainWindow_size.y, "MoveChess", nullptr, nullptr);
    if (!Mainwindow)
    {
        glfwTerminate();
        std::cout << "MainWindow is not created!" << std::endl;
        system("pause");
        return -1;
    }

    glfwSetWindowSizeCallback(Mainwindow, glfwWindowSizeCallBack);
    glfwSetKeyCallback(Mainwindow, glfwKeyCallBack);
    /* Make the window's context current */
    glfwMakeContextCurrent(Mainwindow);

	if(!gladLoadGL())
	{
		std::cout << "Error. glad is not initialized" << std::endl;
        glfwTerminate();
        system("pause");
		return -1;
	}
	
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
	glClearColor(0.5, 0 , 0.2, 1);

    {
        ResourceManager resourceManager(argv[0]);
        auto DefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!DefaultShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            system("pause");
            return -1;
        }

        auto SpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/vertex_sprite.txt", "res/shaders/fragment_sprite.txt");
        if (!DefaultShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            system("pause");
            return -1;
        }

        auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/Desk.png");
        auto sprite = resourceManager.loadSprite("NewSprite", "DefaultTexture", "SpriteShader", 50, 100);
        sprite->setPosition(glm::vec2(300, 100));

        GLuint points_VBO = 0;
        glGenBuffers(1, &points_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colors_VBO = 0;
        glGenBuffers(1, &colors_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoord_VBO = 0;
        glGenBuffers(1, &texCoord_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

        GLuint VAO = 0; 
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_VBO);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        DefaultShaderProgram->use();
        DefaultShaderProgram->setInt("tex", 0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(50.f, 200.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 200.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(MainWindow_size.x), 0.f, static_cast<float>(MainWindow_size.y), -100.f, 100.f);

        DefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        SpriteShaderProgram->use();
        SpriteShaderProgram->setInt("tex", 0);
        SpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(Mainwindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            DefaultShaderProgram->use();
            glBindVertexArray(VAO);
            tex->bind();
            
            DefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            DefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            sprite->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(Mainwindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}