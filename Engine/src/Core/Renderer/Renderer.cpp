#include "Renderer.h"
#include "Core/Logger/Logger.h"
#include <iostream>

void TextureGen::Renderer::InitRenderer(RendererType type, GLFWwindow* window)
{
	switch (type)
	{
	case RendererType::None:
		Logger::LOG_WARN("Renderer type not set\n");
		break;
	case RendererType::Vulkan:
		Logger::LOG_INFO("Vulkan renderer selected\n");
		m_currentRenderer = new VulkanRenderer();
		m_currentRenderer->Init();
		break;
	case RendererType::OpenGL:
		Logger::LOG_INFO("OpenGL renderer selected\n");
		break;
	case RendererType::DirectX:
		Logger::LOG_INFO("DirectX renderer selected\n");
		break;
	default:
		Logger::LOG_WARN("Renderer type not set\n");
		break;
	}
}

TextureGen::Renderer::Renderer()
{}

TextureGen::Renderer::~Renderer()
{
	delete m_currentRenderer;
}
