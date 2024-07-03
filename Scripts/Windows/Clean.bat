setlocal enableDelayedExpansion
@echo off

set "binary_path=Vendor\Binary\"


.\!binary_path!\Python\python.exe .\Scripts\Python\Clean.py %1

if "all"=="%1" (
    echo "Cleaning up the project..."
    echo "Cleaning up Python"
    call :cleanPython
    rmdir /s /q "Scripts\Python\__pycache__"
    rmdir /s /q "!binary_path!"
    echo "Project is cleaned up"
    EXIT /B 0
)
EXIT /B 0

:cleanPython
rmdir /s /q "!binary_path!Python"
EXIT /B 0

