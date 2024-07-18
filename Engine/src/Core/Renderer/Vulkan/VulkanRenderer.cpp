#include "VulkanRenderer.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"

TextureGen::VulkanRenderer::VulkanRenderer(): m_instance(nullptr), m_physicalDevice(nullptr)
{}

TextureGen::VulkanRenderer::~VulkanRenderer()
{
	Shutdown();
}

void TextureGen::VulkanRenderer::Init()
{
	m_instance = new VulkanInstance();
	m_physicalDevice = new VulkanPhysicalDevice(m_instance);
}

void TextureGen::VulkanRenderer::Render()
{}

void TextureGen::VulkanRenderer::Shutdown()
{
	delete m_instance;
	delete m_physicalDevice;
}
