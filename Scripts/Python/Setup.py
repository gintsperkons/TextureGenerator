import sys
import os
import Defines
import Utils

def GetDependencies():
    for module in Defines.requiredPackages:
        if not Utils.IsPackageInstalled(module):
            Utils.InstallPackage(module)
    return

def SetupPremake(enviroment):
    if not os.path.exists(Defines.BinaryPath+"/Premake/premake5"+Defines.premakeExtensions[os.name]):
        Utils.DownloadFile(Defines.PremakeURL[os.name],Defines.TempPath+"/premake"+Defines.premakeArchiveExtensions[os.name])
        Utils.Extract(Defines.TempPath+"/premake"+Defines.premakeArchiveExtensions[os.name],Defines.BinaryPath+"/Premake")
    Utils.ReloadPremake(enviroment)



def CopyTemplate(system):
    if system=="nt":
        with open(f'{Defines.projectPath}/premake.bat', "w+") as file:
            file.write(Defines.batchScriptPremake)
    if system=="posix":
        with open(f'{Defines.projectPath}/premake.sh', "w+") as file:
            file.write(Defines.bashScriptPremake)
             

def SetupResources():
    Utils.DownloadFile("https://fontlibrary.org/assets/downloads/roboto-mono/fa85404374f790dace3a23ea31a1c175/roboto-mono.zip",Defines.TempPath+"/fonts/roboto-mono.zip")
    Utils.ExtractZip(Defines.TempPath+"/fonts/roboto-mono.zip","Vendor/resources/fonts/")


#vs2022 open
if __name__ == "__main__":
    args = sys.argv #vs2022 open yes
    GetDependencies()
    

    if args[1] == '':
        print("Please provide the enviroment for premake or use premake.bat or premake.sh")

    CopyTemplate(os.name)

    SetupPremake(args[1])
    SetupResources()
    
    if len(args) > 2:
        if args[2] == "open":
            Utils.LaunchVS()
    