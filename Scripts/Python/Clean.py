import os
import sys
sys.path.append(f'Scripts/Python')
import Defines
import shutil

def CleanRegardless():
    fileExtensions = [".pyc",".pyo",".sln",".vcxproj",".vcxproj.filters",".vcxproj.user","Makefile",".make"]
    for root, dirs, files in os.walk(Defines.projectPath):
        for file in files:
            for extension in fileExtensions:
                if file.endswith(extension):
                    print("Removing: "+os.path.join(root, file))
                    os.remove(os.path.join(root, file))
        for dir in dirs:
            if dir == "__pycache__":
                print("Removing: "+os.path.join(root, dir))
                shutil.rmtree(os.path.join(root, dir))


    if os.path.exists(Defines.projectPath+"/.vs"):
        print("Removing: "+Defines.projectPath+"/.vs")
        shutil.rmtree(Defines.projectPath+"/.vs")

    if os.path.exists(Defines.projectPath+"/Binaries"):
        print("Removing: "+Defines.projectPath+"/Binaries")
        shutil.rmtree(Defines.projectPath+"/Binaries")



argv = sys.argv
if len(argv) < 2:
    print("Usage: python Clean.py [all]")
elif "all" == argv[1]:
    print("Cleaning up Premake")
    shutil.rmtree(Defines.premakeDir)

CleanRegardless()
