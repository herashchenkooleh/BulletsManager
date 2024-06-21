#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <vulkan/vulkan.hpp>
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "bm/Window.hpp"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace bm
{
	struct Window::Implementation {
		GLFWwindow* m_GLFWWindow = nullptr;
		bool m_Initialized = false;
	};

	Window::Window()
		: m_Implementation(std::make_shared<Implementation>()) {
	}

	Window::~Window() {
		Destroy();
	}

	bool Window::Create(const std::string& InTitle)
	{
		if (m_Implementation->m_Initialized) {
			return m_Implementation->m_Initialized;
		}

    	if (!glfwInit())
		{
			return m_Implementation->m_Initialized;
		}

		glfwSetErrorCallback(glfw_error_callback);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
     	m_Implementation->m_GLFWWindow = glfwCreateWindow(1280, 720, InTitle.c_str(), nullptr, nullptr);
    	m_Implementation->m_Initialized = !!m_Implementation->m_GLFWWindow;

		return m_Implementation->m_Initialized;
	}

	void Window::Destroy() {
		if (m_Implementation->m_GLFWWindow) {
			glfwDestroyWindow(m_Implementation->m_GLFWWindow);
			m_Implementation->m_GLFWWindow = nullptr;
		}

		if (m_Implementation->m_Initialized) {
			glfwTerminate();
		}
		m_Implementation->m_Initialized = false;
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_Implementation->m_GLFWWindow);
	}

	Window::RenderTargetHandle Window::GetRenderTargetHandle() const {
		return reinterpret_cast<void*>(m_Implementation->m_GLFWWindow);
	}
} // namespace CryptoStone::UI