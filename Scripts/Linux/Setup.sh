#!/bin/bash
binaryDir="Vendor/Binary"
pythonVersion="3.12.4"
pythonVersionSmall="312"
archiveLink="https://www.python.org/ftp/python/$pythonVersion/python-$pythonVersion-embed-amd64.zip"
getpipLink="https://bootstrap.pypa.io/get-pip.py"

pushd "$(dirname "$0")/../../" > /dev/null

output=$(python3 -c "print(1+1)")

if [[ "$output" == "2" ]]; then
    echo "Python is working correctly."
else
    echo "Python is not working correctly."
    
    echo "Installing Python"
    sudo apt-get update
    sudo apt-get install -y python3 python3-pip
fi

VENV_DIR="venv"

if [[ ! -d "$VENV_DIR" ]]; then
    echo "Creating a virtual environment..."
    python3 -m venv "$VENV_DIR"
fi

# Activate the virtual environment
source "$VENV_DIR/bin/activate"


python "Scripts/Python/Setup.py" "$1" "$2" "$3"

if [[ -d "$binaryDir/Temp" ]]; then
    echo "Removing Temp"
    rm -rf "$binaryDir/Temp"
fi

echo "Done"

popd
