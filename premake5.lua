include "Dependencies.lua"

workspace("TextureGenerator")
architecture "x64"
configurations {"Debug", "Release", "Dist"}
startproject "Editor"
warnings "Extra"
flags {"MultiProcessorCompile"}
linkoptions { '-Wl,-rpath=\\$$ORIGIN' }


OutputDir = "compiled-%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"
RuntimeDir ="runtime-%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
   include "Vendor/Libraries/GLFW"
   include "Vendor/Libraries/freetype"

group "TextureGenerator"
include "Engine"
include "Editor"
group ""

