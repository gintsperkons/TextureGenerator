#pragma once
#include "Defines.h"
#include "../Base/BaseRenderer.h"


namespace TextureGen
{
	class VulkanInstance;
	class VulkanPhysicalDevice;
	class VulkanRenderer: public BaseRenderer
	{
		VulkanInstance* m_instance;
		VulkanPhysicalDevice* m_physicalDevice;
	public:
		VulkanRenderer();
		~VulkanRenderer();

		void Init();
		void Render();
		void Shutdown();
	};
} // namespace TextureGen