#!/bin/bash
binaryDir="Vendor/Binary"
pythonVersion="3.12.4"
pythonVersionSmall="312"
archiveLink="https://www.python.org/ftp/python/$pythonVersion/python-$pythonVersion-embed-amd64.zip"
getpipLink="https://bootstrap.pypa.io/get-pip.py"
venvDir="venv"  # Directory for virtual environment

# Move to the root directory of the project
pushd "$(dirname "$0")/../../" > /dev/null

# Check if Python is working correctly
output=$(python3 -c "print(1+1)")
if [[ "$output" == "2" ]]; then
    echo "Python is working correctly."
else
    echo "Python is not working correctly."
    echo "Installing Python"
    sudo apt-get update
    sudo apt-get install -y python3 python3-pip
fi

# Check if virtual environment exists
if [[ ! -d "$venvDir" ]]; then
    echo "Creating virtual environment"
    python3 -m venv "$venvDir"
    echo "Virtual environment created."
fi

# Activate the virtual environment
source "$venvDir/bin/activate"

# Upgrade pip and install required dependencies
pip install --upgrade pip

# Run the Python script
python "Scripts/Python/Setup.py" "$1" "$2" "$3"

# Clean up temporary files
if [[ -d "$binaryDir/Temp" ]]; then
    echo "Removing Temp"
    rm -rf "$binaryDir/Temp"
fi

# Deactivate the virtual environment
deactivate

echo "Done"

# Return to the original directory
popd
