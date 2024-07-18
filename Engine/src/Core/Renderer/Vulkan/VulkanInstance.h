#pragma once
#include "Defines.h"
#include <vulkan/vulkan.h>
#include <vector>

namespace TextureGen
{
	class VulkanInstance
	{
		VkInstance m_Instance;
		std::vector<const char*> GetInstanceExtensions();
		bool CheckInstanceExtensionSupport(std::vector<const char*> extensions);
	public:
		VulkanInstance();
		~VulkanInstance();
	};
}

