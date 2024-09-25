#!/bin/bash
directory="Vendor/Binary/"

pushd "$(dirname "$0")/../../" > /dev/null

echo "Cleaning Up Files"

if [[ -d "$directory" ]]; then
    echo "Cleaning Up Generated Files"
    python3 "$(pwd)/Scripts/Python/Clean.py" "$1"
fi

if [[ "$1" == "all" ]]; then
    if [[ -d "$directory" ]]; then
        echo "Cleaning $directory"
        rm -rf "$directory"
    fi
fi

echo "Done"

popd > /dev/null
