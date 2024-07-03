import os
import sys
sys.path.append(f'Scripts/Python')
import Defines


dependencies = [
    "requests"
]

print(f"Installing dependencies for python")
print(Defines.pipExe)

#install dependencies
for dependency in dependencies:
    #check if the dependency is already installed
    import importlib.util
    spec = importlib.util.find_spec(dependency)
    if spec is not None:
        print(f"{dependency} is already installed")
        continue
    command = f'"{Defines.pythonExe}" {Defines.LibPath}pip install {dependency}'
    print(command)
    os.system(command)