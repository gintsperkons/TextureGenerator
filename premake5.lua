include "Dependencies.lua"  

workspace "TextureGenerator"  
configurations { "Debug", "Release", "Dist" }
architecture "x64"
startproject "TextureGenerator"


OutputDir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"

group "Dependencies"
include "Vendor/Libraries/GLFW"
group ""



include "Engine"
include "Editor"

    

