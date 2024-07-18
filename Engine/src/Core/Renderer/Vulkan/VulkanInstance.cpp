#include "VulkanInstance.h"
#include <GLFW/glfw3.h>
#include <stdexcept>



TextureGen::VulkanInstance::VulkanInstance()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "TextureGen";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "TextureGen";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3;


	std::vector<const char*> instanceExtensions = GetInstanceExtensions();
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Vulkan Instance");
	}




}

std::vector<const char *> TextureGen::VulkanInstance::GetInstanceExtensions()
{
	uint32_t glfwExtensionCount = 0;
	std::vector<const char*> instanceExtensions = std::vector<const char*>();

	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (uint32_t i = 0; i < glfwExtensionCount; i++)
	{
		instanceExtensions.push_back(glfwExtensions[i]);
	}

	if (!CheckInstanceExtensionSupport(instanceExtensions))
	{
		std::runtime_error("Required instance extensions not supported");
	}

	return instanceExtensions;
}

bool TextureGen::VulkanInstance::CheckInstanceExtensionSupport(std::vector<const char *> extensions)
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

	for (const auto &extension : extensions)
	{
		bool hasExtension = false;
		for (const auto &availableExtension : availableExtensions)
		{
			if (strcmp(extension, availableExtension.extensionName))
			{
				hasExtension = true;
				break;
			}
		}
		if (!hasExtension)
		{
			printf("Extension %s not supported\n", extension);
			return false;
		}
	}

	return true;
}

TextureGen::VulkanInstance::~VulkanInstance()
{
	vkDestroyInstance(m_Instance, nullptr);
}
