

#!/bin/bash

directory="Vendor/Binary/"

pushd "$(dirname "$0")" > /dev/null

echo "Calling Premake"

if [ -d "$directory" ]; then
    echo "Running Premake"
    "$directory/Premake/premake5" "$@"
fi

echo "Done"

popd > /dev/null
