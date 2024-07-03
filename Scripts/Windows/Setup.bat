setlocal enableDelayedExpansion
@echo off

set "python_version=3.12.4"
set "binary_path=Vendor\Binary\"
set "python_path=!binary_path!Python\python.exe"

pushd "%~dp0/../../"
echo "Setting up the project..."
echo "Validating Python"
if not exist %python_path% (
    echo "Python is not installed"
    echo "Downloading Python"
    if not exist !binary_path!Temp mkdir !binary_path!Temp
    powershell -Command "Invoke-WebRequest https://www.python.org/ftp/python/!python_version!/python-!python_version!-embed-amd64.zip -OutFile !binary_path!Temp/python.zip"
    echo "Extracting Python"
    powershell -Command "Expand-Archive -Path '!binary_path!Temp/python.zip' -DestinationPath '!binary_path!/Python' -Force"
    echo "Python is installed"
    .\Python\python.exe .\Scripts\Python\Setup.py
) else (
    echo "Python is installed"
)
echo "Validating pip"
if not exist !binary_path!Python/Scripts/pip.exe (
    echo "pip is not installed"
    echo "Downloading pip"
    powershell -Command "Invoke-WebRequest https://bootstrap.pypa.io/get-pip.py -OutFile !binary_path!Temp/get-pip.py"
    echo "Installing pip"
    .\!binary_path!\Python\python.exe !binary_path!Temp/get-pip.py
    echo "pip is installed"
) else (
    echo "pip is installed"
)
echo "Cleaning up"

.\!binary_path!\Python\python.exe .\Scripts\Python\Setup.py
rmdir /s /q !binary_path!Temp


.\Vendor\Binary\Premake\Premake5.exe %1

popd
