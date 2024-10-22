local os = require("os")
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Vendor/Library/GLFW/include"
IncludeDir["GLM"] = "%{wks.location}/Vendor/Library/GLM"
IncludeDir["GLAD"] = "%{wks.location}/Vendor/Library/GLAD/include"
IncludeDir["FreeType"] = "%{wks.location}/Vendor/Library/freetype/include"