local os = require("os")
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Vendor/Libraries/GLFW/include"
IncludeDir["GLM"] = "%{wks.location}/Vendor/Libraries/GLM"
IncludeDir["GLAD"] = "%{wks.location}/Vendor/Libraries/GLAD/include"
IncludeDir["FreeType"] = "%{wks.location}/Vendor/Libraries/freetype/include"
IncludeDir["STB"] = "%{wks.location}/Vendor/Libraries/STB"
IncludeDir["FastNoise2"] = "%{wks.location}/Vendor/Libraries/FastNoise2/include"