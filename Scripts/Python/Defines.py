import os
import sys

projectPath = os.getcwd()
pythonDir = "Vendor/Binary/Python"
pythonExe = sys.executable
pipExe = pythonDir + "/Scripts/pip.exe"
LibPath = pythonDir+"\\Lib\\site-packages\\"
premakeDir = "Vendor/Binary/Premake"
sys.path.append(f'{LibPath}')