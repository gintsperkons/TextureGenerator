#pragma once
#include "Defines.h"
#include "../Base/BaseRenderer.h"


namespace TextureGen
{
	class VulkanInstance;
	class VulkanRenderer: public BaseRenderer
	{
		VulkanInstance* m_instance;
	public:
		VulkanRenderer();
		~VulkanRenderer();

		void Init();
		void Render();
		void Shutdown();
	};
} // namespace TextureGen