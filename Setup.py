import Scripts.Python.Utils as Utils
import shutil
import os 


if __name__ == "__main__":
    Utils.downloadFile("https://fontlibrary.org/assets/downloads/roboto-mono/fa85404374f790dace3a23ea31a1c175/roboto-mono.zip","Vendor/Temp/roboto-mono.zip")
    Utils.extract("Vendor/Temp/roboto-mono.zip","Vendor/resources/fonts/")
    if (os.path.exists("Vendor/Temp/")):
        shutil.rmtree("Vendor/Temp/")

    if os.name == 'nt':
        with open("run.bat", "w") as file:
            file.write(
            "@echo off\n"
            "pushd .\\Binaries\\runtime-windows-x86_64-Debug\\\n"
            "if %errorlevel%==0 (\n"
            "    start Editor.exe\n"
            ")\n"
            "popd\n"
            )