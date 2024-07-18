#include "Renderer.h"
#include <iostream>

void TextureGen::Renderer::InitRenderer(RendererType type, GLFWwindow* window)
{
	switch (type)
	{
	case RendererType::None:
		printf("Renderer type not set\n");
		break;
	case RendererType::Vulkan:
		printf("Vulkan renderer selected\n");
		m_currentRenderer = new VulkanRenderer();
		break;
	case RendererType::OpenGL:
		printf("OpenGL renderer selected\n");
		break;
	case RendererType::DirectX:
		printf("DirectX renderer selected\n");
		break;
	default:
		printf("Renderer type not set\n");
		break;
	}
}

TextureGen::Renderer::Renderer()
{}

TextureGen::Renderer::~Renderer()
{
	delete m_currentRenderer;
}
