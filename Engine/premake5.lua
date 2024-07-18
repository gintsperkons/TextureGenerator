project "Engine"
kind "SharedLib"
language "C++"
cppdialect "C++20"
targetdir "Binaries/%{cfg.buildcfg}"
staticruntime "off"


targetdir("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
debugdir("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")

includedirs {"src",
"%{IncludeDir.GLFW}",
"%{IncludeDir.GLM}",
"%{IncludeDir.VulkanSDK}",
}

links {
    "GLFW",
    "%{Library.Vulkan}"
}



files {"src/**.h", "src/**.cpp"}



-- prebuildcommands
-- {
--         "%{prj.location}\\Shaders\\CompileShaders.bat"
-- }

postbuildcommands
{   
    "{ECHO} \"%{prj.location}\"",
    "{mkdir} \"%{wks.location}\\Binaries\\" .. OutputDir .. "\\Editor\\\"",
    "{COPYFILE} \"%{cfg.buildtarget.relpath}\" \"%{wks.location}\\Binaries\\" .. OutputDir .. "\\Editor\\\"",
--     "{mkdir} %{wks.location}\\Binaries\\" .. OutputDir .. "\\TestBed\\Shaders\\",
--     "{COPYDIR} %{prj.location}\\Shaders %{wks.location}\\Binaries\\" .. OutputDir .. "\\TestBed\\Shaders\\"
}



filter "system:windows"
systemversion "latest"
defines {"WINDOWS"}

filter "configurations:Debug"
defines {"TDEBUG"}
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines {"TRELEASE"}
runtime "Release"
optimize "On"
symbols "On"

filter "configurations:Dist"
defines {"TDIST"}
runtime "Release"
optimize "On"
symbols "Off"