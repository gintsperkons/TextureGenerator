import os
import sys

pythonDir = "Vendor/Binary/Python"
pythonExe = sys.executable
pipExe = pythonDir + "/Scripts/pip.exe"
LibPath = pythonDir+"\\Lib\\site-packages\\"
sys.path.append(f'{LibPath}')