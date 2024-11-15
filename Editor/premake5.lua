project "Editor"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
targetdir "Binaries/%{cfg.buildcfg}"
staticruntime "off"

includedirs {"Source",
"%{wks.location}/Engine/Source"

}

links {
 "Engine"
}


targetdir("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
debugdir("%{wks.location}/Binaries/" .. RuntimeDir .. "\\")
debugcommand("%{wks.location}/Binaries/" .. RuntimeDir .. "/Editor.exe")
targetname("%{prj.name}")





flags {
    "MultiProcessorCompile"
}



files {"Source/**.h", "Source/**.cpp"}



filter "system:windows"
postbuildcommands {"{MKDIR} %{wks.location}/Binaries/" .. RuntimeDir .. "/",
                   "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}/Binaries/" .. RuntimeDir .. "/",

}

systemversion "latest"
defines {"WINDOWS"}

filter "system:linux"
postbuildcommands {"{MKDIR} %{wks.location}/Binaries/" .. RuntimeDir .. "/",
                   "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}/Binaries/" .. RuntimeDir .. "/",
                   "echo '#!/bin/bash' > %{wks.location}/run.sh", -- Create run.sh
"echo 'pushd Binaries/" .. RuntimeDir .. "/' >> %{wks.location}/run.sh", -- Change to script directory
"echo './%{prj.name}' >> %{wks.location}/run.sh", -- Command to run the executable
"chmod +x %{wks.location}/run.sh" -- Make the script executable   
}



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