setlocal enableDelayedExpansion
@echo off

set "binary_path=Vendor\Binary\"
if "all"=="%1" (
    echo "Cleaning up the project..."
    echo "Cleaning up Python"
    call :cleanPython
    rmdir /s /q "!binary_path!"
    echo "Project is cleaned up"
)

:cleanPython
rmdir /s /q "!binary_path!Python"
EXIT /B 0

