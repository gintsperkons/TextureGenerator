workspace "TextureGenerator"  
configurations { "Debug", "Release", "Dist" }
architecture "x64"
startproject "TextureGenerator"


OutputDir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"

include "Editor"
    

