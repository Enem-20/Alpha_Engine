#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/vec2.hpp>
#include<glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Algorithms/hash_table.h"

#include <iostream>
#include <algorithm>

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
glm::ivec2 g_MainWindow_size(1080, 1080);
glm::ivec2 g_BoardSize(g_MainWindow_size);
unsigned int g_board_left_offset = 0;
unsigned int g_board_bottom_offset = 0;

void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
    g_MainWindow_size.x = width;
    g_MainWindow_size.y = height;

    if (width > height)
    {
        g_board_left_offset = (width - height)/2;
        width = height;
    }
    else if (height > width)
    {
        g_board_bottom_offset = (height - width)/2;
        height = width;
    }

    g_BoardSize.x = width;
    g_BoardSize.y = height;

    glViewport(g_board_left_offset, g_board_bottom_offset, g_BoardSize.x, g_BoardSize.y);
}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        glm::dvec2 cursorPos_OnClick;
        glfwGetCursorPos(window, &cursorPos_OnClick.x, &cursorPos_OnClick.y);

        int board_pos_x = cursorPos_OnClick.x - g_board_left_offset;
        int board_pos_y = g_BoardSize.y - cursorPos_OnClick.y + g_board_bottom_offset;

        if (board_pos_x >= 0 && board_pos_x < g_BoardSize.x && board_pos_y >= 0 && board_pos_y < g_BoardSize.x)
        {
            unsigned int cellSize = (g_BoardSize.x >> 3);
            size_t cell_x = std::min(board_pos_x / cellSize, 7u);
            size_t cell_y = std::min(board_pos_y / cellSize, 7u);
            std::cout << "cell (" << cell_x << ", " << cell_y  << ")" <<  std::endl;
         }
    }
}

int main(int argc, char** argv)
{/*
    hash_table<int, long long> some;

    std::cout << "Before resize: ";
    some[4] = 5;
    std::cout << some.get(4) << std::endl;
    some[10] = 20;
    std::cout << some.get(10) << std::endl;
    some[200000] = 5000000004445;
    std::cout << some.get(200000) << std::endl;


    some.set_size(256);

    std::cout << "After resize: ";
    std::cout << some.get(4) << std::endl;
    std::cout << some.get(10) << std::endl;
    std::cout << some.get(200000) << std::endl;
    
    std::cout << "Hash value on 4: " << some[4];*/

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
    GLFWwindow* Mainwindow = glfwCreateWindow(g_MainWindow_size.x, g_MainWindow_size.y, "MoveChess", nullptr, nullptr);
    if (!Mainwindow)
    {
        glfwTerminate();
        std::cout << "MainWindow is not created!" << std::endl;
        system("pause");
        return -1;
    }

    glfwSetWindowSizeCallback(Mainwindow, glfwWindowSizeCallBack);
    glfwSetKeyCallback(Mainwindow, glfwKeyCallBack);
    glfwSetMouseButtonCallback(Mainwindow, glfwMouseCallBack);
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

        auto Desk = resourceManager.loadTexture("Desk", "res/textures/Desk.png");

       /* std::vector<std::string> subTexturesNames = { "Black_castle", "Black_knight", "Black_bishop", "Black_queen", "Black_king", "Black_pawn", "White_castle", "White_knight", "White_bishop", "White_queen", "White_king", "White_pawn" };
        auto TextureAtlas = resourceManager.loadTextureAtlas("DefaultTextureAtlas", "res/textures/GameObjects_Atlas.png", std::move(subTexturesNames), 69, 69);


        auto sprite = resourceManager.loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 69, 69, "White_knight");
        sprite->setPosition(glm::vec2(300, 100));*/

        auto sprite_Desk = resourceManager.loadSprite("sprite_Desk", "Desk", "SpriteShader", g_BoardSize.x, g_BoardSize.y, "");

        //glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        //modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(50.f, 200.f, 0.f));

        //glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        //modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 200.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_BoardSize.x), 0.f, static_cast<float>(g_BoardSize.y), -100.f, 100.f);

        SpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        SpriteShaderProgram->use();
        SpriteShaderProgram->setInt("tex", 0);
        SpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(Mainwindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            //SpriteShaderProgram->use();

            sprite_Desk->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(Mainwindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}