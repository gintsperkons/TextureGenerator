local os = require("os")
VULKAN_SDK = os.getenv("VULKAN_SDK")

function isClangAvailable()
    local clangTest = os.outputof("clang --version")
    return clangTest ~= nil
end

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Vendor/Library/GLFW/include"
IncludeDir["GLM"] = "%{wks.location}/Vendor/Library/GLM"
IncludeDir["GLAD"] = "%{wks.location}/Vendor/Library/GLAD/include"

