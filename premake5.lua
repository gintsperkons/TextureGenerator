include "Dependencies.lua"

workspace("TextureGenerator")
architecture "x64"
configurations {"Debug", "Release", "Dist"}
startproject "Editor"
flags {"MultiProcessorCompile"}

filter "system:linux"
linkoptions {'-Wl,-rpath=\\$$ORIGIN'}
filter ""



OutputDir = "compiled-%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"
RuntimeDir ="runtime-%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
   include "Vendor/Libraries/GLFW"
   include "Vendor/Libraries/freetype"
   include "Vendor/Libraries/FastNoise2"
   include "Vendor/Libraries/TinyFileDialog"

group "TextureGenerator"
include "Engine"
include "Editor"
group ""

