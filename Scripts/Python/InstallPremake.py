import os
import sys
sys.path.append(f'Scripts/Python')
import Defines
import Utils
import zipfile
import tarfile


tempPremakeArchive = "Vendor/Binary/Temp/Premake"

premakeURL = {"nt":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip",
              "posix":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz"}


if not os.path.exists(Defines.premakeDir):
    extension = ".tar.gz" if os.name == "posix" else ".zip"
    if not os.path.exists(tempPremakeArchive):
        print("Downloading Premake")
        Utils.downloadFile(premakeURL[os.name], tempPremakeArchive+extension)
    print("Extracting Premake")
    if extension == ".tar.gz":
        with tarfile.open(tempPremakeArchive+extension, 'r:gz') as tar_ref:
            tar_ref.extractall(Defines.premakeDir)
    else:
        with zipfile.ZipFile(tempPremakeArchive+extension, 'r') as zip_ref:
            zip_ref.extractall(Defines.premakeDir)
    print("Cleaning up")
    os.remove(tempPremakeArchive+extension)