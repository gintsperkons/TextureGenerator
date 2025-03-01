@echo off
:: Step 1: Run setup.bat
echo Running setup.bat...
call ./setup.bat

:: Step 2: Build the solution with MSBuild
echo Running MSBuild on TextureGenerator.sln...
MSBuild.exe TextureGenerator.sln

:: Step 3: Run run.bat to fix
echo Running run.bat...
call ./run.bat fix

:: Done
echo All steps completed.
pause
