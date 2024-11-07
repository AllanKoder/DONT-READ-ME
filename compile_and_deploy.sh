#!/bin/bash
# A script to help the deployment process of files

# Base directory where the C++ source files are located
BASE_DIR="."
# Destination directory for CGI executables
CGI_BIN="/usr/lib/cgi-bin"

# Loop through all .cpp files in the base directory and its subdirectories
find "$BASE_DIR" -name "*.cpp" | while read -r cpp_file; do
    # Get the directory of the current .cpp file
    dir=$(dirname "$cpp_file")
    # Get the base name of the .cpp file without extension
    base_name=$(basename "$cpp_file" .cpp)
    
    # Compile the C++ file
    g++ "$cpp_file" -lmariadbcpp -lcgicc -o "$dir/$base_name.cgi"
    
    # Check if compilation was successful
    if [[ $? -eq 0 ]]; then
        # Move the compiled CGI executable to /usr/lib/cgi-bin/
        mv "$dir/$base_name.cgi" "$CGI_BIN/"
        echo "Successfully compiled and deployed: $base_name.cgi"
    else
        echo "Failed to compile: $cpp_file"
    fi
done

echo "All done!"