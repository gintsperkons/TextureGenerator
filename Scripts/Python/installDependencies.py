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
    
    command = f'"{Defines.pythonExe}" {Defines.LibPath}pip install {dependency}'
    print(command)
    os.system(command)