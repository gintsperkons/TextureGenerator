project "Engine"
    kind "SharedLib"
    language "C++"
    targetdir "Binaries\\%{cfg.buildcfg}"
    cppdialect "C++20"


    files {"Source\\**.h", "Source\\**.cpp"}



    includedirs
    {
        "Source",
        IncludeDir["GLFW"],
        IncludeDir["GLM"]
    }

    links 
    {
        "GLFW"
    }

    targetdir ("%{wks.location}\\Binaries\\" .. OutputDir .. "\\%{prj.name}")
    objdir ("%{wks.location}\\Binaries\\Intermediates\\" .. OutputDir .. "\\%{prj.name}")
    debugdir("%{wks.location}\\Binaries\\" .. OutputDir .. "\\%{prj.name}")

    flags {
        "MultiProcessorCompile"
    }

    postbuildcommands
    {   
        "{ECHO} \"%{prj.location}\"",
        "{MKDIR} \"%{wks.location}/Binaries/" .. OutputDir .. "/Editor/\"",
        "{COPYFILE} \"%{cfg.buildtarget.relpath}\" \"%{wks.location}/Binaries/" .. OutputDir .. "/Editor/\""
    }

    filter "system:windows"
        systemversion "latest"
        defines {"WINDOWS"}

    filter "configurations:Debug"
        defines {"TEXPORT","TDEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {"TEXPORT","TRELEASE"}
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines {"TEXPORT","TDIST"}
        runtime "Release"
        optimize "On"
        symbols "Off"

    
    