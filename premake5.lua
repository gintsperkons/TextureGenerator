include "Dependencies.lua"

workspace("TextureGenerator")
architecture "x64"
configurations {"Debug", "Release", "Dist"}
startproject "Editor"

OutputDir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"

group "Dependencies"
    include "Vendor/Library/GLFW"

group "TextureGenerator"
include "Engine"
include "Editor"
group ""

