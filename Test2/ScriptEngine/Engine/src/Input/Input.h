#pragma once

#include <list>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "../GameTypes/GameTypes.h"

class Input
{
public:
	static void SetCallBacks(GLFWwindow* window);

	inline static Figure* selected_object;
	static void AddListener();

	class OnClick
	{
	public:
		OnClick() { states = States::Idle; }

		OnClick& operator+=(const OnClick& element)
		{
			elements.push_back(element);
		}

		virtual void onClick()
		{
			for (auto it : elements)
			{
				it.onClick();
			}
		}

		enum States {Idle, Down, Pressed, Up};

		States states;
	protected:
		static std::list<OnClick> elements;
	};

	static void glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods);
	static void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height);
	static void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void OnClick();

	std::list<GameObject> listeners;
	
	class Button : OnClick
	{
		
	};
};