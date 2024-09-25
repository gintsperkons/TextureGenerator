
import sys
import os
requiredPackages = ["requests"]
pythonBinary = os.getcwd()+"/Vendor/Binary/Python/python.exe"


PremakeURL = {
    "nt":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip",
    "posix":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz"
    }



projectPath = os.getcwd()
TempPath = projectPath+"/Vendor/Binary/Temp"
BinaryPath = "Vendor/Binary/"

premakeExtensions =  {
    "nt":".exe",
    "posix":""
}



premakeArchiveExtensions =  {
    "nt":".zip",
    "posix":".tar.gz"
}


batchScriptPremake = f"""
@echo off
setlocal enabledelayedexpansion
set directory=Vendor\\Binary\\

pushd %~dp0
echo Calling Premake
if exist !directory! (
    echo Running Premake
    call "!cd!\\!directory!Premake\\premake5.exe" %*
)
echo Done
popd
"""