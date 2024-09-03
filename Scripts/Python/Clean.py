
import sys
import os
import shutil
import Defines



args = sys.argv

if len(args) >=2 and (args[1] == "generated" or args[1] == "gen"):
    fileExtensions = [".pyc",".pyo",".sln",".vcxproj",".vcxproj.filters",".vcxproj.user","Makefile",".code-workspace","CMakeCache.txt","cmake_install.cmake"]
    folderNames = ["__pycache__","Binaries",".vs",".vscode","CMakeFiles"]
else:
    fileExtensions = []
    folderNames = ["Binaries"]



for root, dirs, files in os.walk(Defines.projectPath):
    for file in files:
        for extension in fileExtensions:
            if file.endswith(extension):
                os.remove(os.path.join(root, file))
                print("Removed: " + os.path.join(root, file))
    for dir in dirs:
        if dir in folderNames:
            shutil.rmtree(os.path.join(root, dir))
            print("Removed: " + os.path.join(root, dir))