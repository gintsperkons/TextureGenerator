#include "VulkanRenderer.h"
#include "VulkanInstance.h"

TextureGen::VulkanRenderer::VulkanRenderer(): m_instance(nullptr)
{}

TextureGen::VulkanRenderer::~VulkanRenderer()
{
	Shutdown();
}

void TextureGen::VulkanRenderer::Init()
{
	m_instance = new VulkanInstance();
}

void TextureGen::VulkanRenderer::Render()
{}

void TextureGen::VulkanRenderer::Shutdown()
{
	delete m_instance;
}
