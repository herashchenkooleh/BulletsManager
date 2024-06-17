#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "bm/Window.hpp"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace bm
{
	struct Window::Implementation
	{
		GLFWwindow* m_GLFWWindow = nullptr;
	};

	Window::Window()
		: m_Implementation(std::make_shared<Implementation>())
	{
	}

	Window::~Window()
	{
    	glfwDestroyWindow(m_Implementation->m_GLFWWindow);
    	glfwTerminate();
	}

	bool Window::Create(const std::string& InTitle)
	{
		glfwSetErrorCallback(glfw_error_callback);
    	if (!glfwInit())
		{
			return false;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
     	m_Implementation->m_GLFWWindow = glfwCreateWindow(1280, 720, InTitle.c_str(), nullptr, nullptr);
    	if (m_Implementation->m_GLFWWindow == nullptr)
		{
			return false;
		}

		return true;
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_Implementation->m_GLFWWindow);
	}
} // namespace CryptoStone::UI