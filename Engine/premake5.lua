project "Engine"
kind "SharedLib"
language "C++"
targetdir "Binaries\\%{cfg.buildcfg}"
cppdialect "C++20"
visibility "Hidden"

files {"Source\\**.h", "Source\\**.cpp", "Source\\glad.c"}

includedirs {"Source", IncludeDir["GLFW"], IncludeDir["GLM"], IncludeDir["GLAD"], IncludeDir["FreeType"]}

targetdir("%{wks.location}\\Binaries\\" .. OutputDir .. "\\%{prj.name}")
objdir("%{wks.location}\\Binaries\\Intermediates\\" .. OutputDir .. "\\%{prj.name}")
debugdir("%{wks.location}\\Binaries\\" .. OutputDir .. "\\%{prj.name}")
flags {"MultiProcessorCompile"}


filter "system:windows"
postbuildcommands {"{MKDIR} %{wks.location}\\Binaries\\" .. RuntimeDir .. "\\",
                   "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}\\Binaries\\" .. RuntimeDir .. "\\",
                   "{COPYDIR} \"%{wks.location}\\Vendor\\resources\\\" \"%{wks.location}\\Binaries\\" .. RuntimeDir .."\\resources\\\"", 
                   "{COPYDIR} \"%{wks.location}\\Engine\\Shaders\\\" \"%{wks.location}\\Binaries\\" .. RuntimeDir .. "\\Shaders\\\"" 
}
links {"freetype", "GLFW", "opengl32.lib", "gdi32.lib", "user32.lib", "shell32.lib"}

filter "system:linux"
postbuildcommands {"{MKDIR} %{wks.location}\\Binaries\\" .. RuntimeDir .. "\\",
                   "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}\\Binaries\\" .. RuntimeDir .. "\\",
                   "{COPYDIR} \"%{wks.location}\\Vendor\\resources\" \"%{wks.location}\\Binaries/\\" .. RuntimeDir .."\\\"",
                    "{COPYDIR} \"%{wks.location}\\Engine\\Shaders\" \"%{wks.location}\\Binaries\\" .. RuntimeDir .. "\\\"" -- "{ECHO} \"%{prj.location}\"",
}

links {"freetype", "GL", "GLFW", "wayland-client", "wayland-egl", "EGL", "GL"}



filter "system:windows"
systemversion "latest"
defines {"WINDOWS"}

filter "configurations:Debug"
defines {"TEXPORT", "TDEBUG"}
runtime "Debug"
symbols "On"
runtime "Debug"

filter "configurations:Release"
defines {"TEXPORT", "TRELEASE"}
runtime "Release"
optimize "On"
symbols "On"
runtime "Release"

filter "configurations:Dist"
defines {"TEXPORT", "TDIST"}
runtime "Release"
optimize "On"
symbols "Off"
runtime "Release"

