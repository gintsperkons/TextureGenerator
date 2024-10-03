include "Dependencies.lua"

workspace("TextureGenerator")
architecture "x64"
configurations {"Debug", "Release", "Dist"}
startproject "Editor"

if isClangAvailable() then
    toolset "clang"
    print("Clang detected, using Clang.")
else
    toolset "gcc"
    print("Clang not found, using GCC.")
end

OutputDir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"

group "Dependencies"
    include "Vendor/Library/GLFW"

group "TextureGenerator"
include "Engine"
include "Editor"
group ""

