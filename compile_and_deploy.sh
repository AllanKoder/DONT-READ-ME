#!/bin/bash
# A script to help the deployment process of files

# Store the initial working directory
INITIAL_DIR=$(pwd)

# Base directory where the C++ source files are located
BASE_DIR="$INITIAL_DIR/Routes"
# Destination directory for CGI executables
CGI_BIN="/usr/lib/cgi-bin"

# Loop through all .cpp files in the base directory and its subdirectories
find "$BASE_DIR" -name "*.cpp" | while read -r cpp_file; do
    # Get the directory of the current .cpp file
    dir=$(dirname "$cpp_file")
    # Get the base name of the .cpp file without extension
    base_name=$(basename "$cpp_file" .cpp)

    # Go to the directory containing the current .cpp file
    cd "$dir" || { echo "Failed to change to directory: $dir"; continue; }

    # Compile using make
    make

    # Check if compilation was successful
    if [[ $? -eq 0 ]]; then
        # Move the compiled CGI executable to /usr/lib/cgi-bin/
        if [[ -f "$base_name.cgi" ]]; then
            mv "$base_name.cgi" "$CGI_BIN/"
            echo "Successfully compiled and deployed: $base_name.cgi"
            echo ""
        else
            echo "Compiled file not found: $base_name.cgi"
        fi
    else
        echo "Failed to compile: $cpp_file"
    fi

    # Return to the initial directory
    cd "$INITIAL_DIR" || { echo "Failed to return to initial directory"; exit 1; }
done

echo "All done!"