#pragma once
#include "Defines.h"
#include "Base/BaseRenderer.h"
#include "Vulkan/VulkanRenderer.h"



struct GLFWwindow;
namespace TextureGen
{
	typedef enum RendererType
	{
		None = 0,
		Vulkan,
		OpenGL,
		DirectX
	} RendererType;

	class Renderer
	{
		
		BaseRenderer *m_currentRenderer = nullptr;

	public:
		TAPI Renderer();
		TAPI void InitRenderer(TextureGen::RendererType type, GLFWwindow* window);
		TAPI ~Renderer();

	};
	

}