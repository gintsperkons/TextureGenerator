import os
import sys
sys.path.append(f'Scripts/Python')
import Defines
import Utils
import zipfile

premakeDir = "Vendor/Binary/Premake"
tempPremakeArchive = "Vendor/Binary/Temp/Premake.zip"

premakeURL = {"nt":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"
              }


if not os.path.exists(premakeDir):
    if not os.path.exists(tempPremakeArchive):
        print("Downloading Premake")
        Utils.downloadFile(premakeURL[os.name], tempPremakeArchive)
    print("Extracting Premake")
    with zipfile.ZipFile(tempPremakeArchive, 'r') as zip_ref:
        zip_ref.extractall(premakeDir)
    print("Cleaning up")
    os.remove(tempPremakeArchive)