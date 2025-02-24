import os
import sys
import shutil
import codecs # For reading and writing files with utf-8 specific encoding (required for Windows)
import re 

# (c) 2024-2025 Tomáš Mark
# This script is licensed under the MIT license

source_dir = "source"
include_dir = "include"
standalone_dir = "standalone"

# forbidden words that cannot be used in the project name
FORBIDDEN_WORDS = [
    'build', 'standalone', 'library', 'default', 'debug', 'release', 'relwithdebinfo',
    'minsizerel'
]

def check_forbidden_words(name):
    """
    Check if the name contains any forbidden words (case-insensitive).
    Only matches whole words, not partial matches.
    Returns False if a forbidden word is found, True otherwise.
    """
    name_lower = name.lower()
    for word in FORBIDDEN_WORDS:
        # Create pattern that matches word boundaries
        pattern = r'\b' + re.escape(word.lower()) + r'\b'
        if re.search(pattern, name_lower):
            print(f"Error: The name '{name}' contains forbidden word '{word}'")
            return False
    return True

def rename_project(old_lib_name, new_lib_name, old_standalone_name, new_standalone_name):
    # Add validation at the start of the function
    if not check_forbidden_words(new_lib_name):
        sys.exit(1)
    if not check_forbidden_words(new_standalone_name):
        sys.exit(1)

    # Convert to lowercase and uppercase
    old_lib_name_lower = old_lib_name.lower()
    new_lib_name_lower = new_lib_name.lower()
    old_lib_name_upper = old_lib_name.upper()
    new_lib_name_upper = new_lib_name.upper()

    # Library can't have the same name as the standalone project
    if new_lib_name == new_standalone_name:
        print("Error: new_lib_name and new_standalone_name must be different")
        sys.exit(1)

    # List of files where the project names should be changed
    files = [
        "CMakeLists.txt",
        f"{standalone_dir}/CMakeLists.txt",
        f"{include_dir}/{old_lib_name}/{old_lib_name}.hpp",
        f"{source_dir}/{old_lib_name}.cpp",
        f"{standalone_dir}/{source_dir}/Main.cpp",
        f"{include_dir}/Logger.hpp",
        ".vscode/launch.json",
        ".vscode/tasks.json",
        "LICENSE",
        # Add more files as needed
    ]

    # Replace the old library name with the new one in each file
    for file in files:
        if os.path.isfile(file):
            with codecs.open(file, 'r', encoding='utf-8') as f:
                content = f.read()
            content = content.replace(old_lib_name, new_lib_name)
            content = content.replace(old_standalone_name, new_standalone_name)
            content = content.replace(old_lib_name_lower, new_lib_name_lower)
            content = content.replace(old_lib_name_upper, new_lib_name_upper)
            with codecs.open(file, 'w', encoding='utf-8') as f:
                f.write(content)
            print(f"Renamed project names in file: {file}")
        else:
            print(f"File {file} does not exist!")

    # Rename files
    if os.path.isfile(f"{source_dir}/{old_lib_name}.cpp"):
        os.rename(f"{source_dir}/{old_lib_name}.cpp", f"{source_dir}/{new_lib_name}.cpp")
        print(f"Renamed file: {source_dir}/{old_lib_name}.cpp to {source_dir}/{new_lib_name}.cpp")

    if os.path.isfile(f"{include_dir}/{old_lib_name}/{old_lib_name}.hpp"):
        os.rename(f"{include_dir}/{old_lib_name}/{old_lib_name}.hpp", f"{include_dir}/{old_lib_name}/{new_lib_name}.hpp")
        print(f"Renamed file: {include_dir}/{old_lib_name}/{old_lib_name}.hpp to {include_dir}/{old_lib_name}/{new_lib_name}.hpp")

    # Rename directories
    if os.path.isdir(f"{include_dir}/{old_lib_name}"):
        os.rename(f"{include_dir}/{old_lib_name}", f"{include_dir}/{new_lib_name}")
        print(f"Renamed directory: {include_dir}/{old_lib_name} to {include_dir}/{new_lib_name}")

    print("\033[92mProject renaming completed.\033[0m")

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage: python3 SolutionRenamer.py <OldLibName> <NewLibName> <OldStandaloneName> <NewStandAloneName>")
        sys.exit(1)

    old_lib_name = sys.argv[1]
    new_lib_name = sys.argv[2]
    old_standalone_name = sys.argv[3]
    new_standalone_name = sys.argv[4]

    rename_project(old_lib_name, new_lib_name, old_standalone_name, new_standalone_name)
    
