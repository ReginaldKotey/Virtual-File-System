# Virtual-File-System
Virtual File System is a C++ project that simulates a file system from scratch using custom-built data structures like stacks, queues, and vectors. It showcases the power of efficient data management by mimicking real-world file operations in a virtual environment.

## Features

### Core Commands
- **`help`**: Display a list of available commands and their descriptions.
- **`pwd`**: Show the current working directory.
- **`ls`**: List the contents of the current directory.
- **`mkdir <dir_name>`**: Create a new directory.
- **`touch <file_name> <size>`**: Create a new file with a specified size (in bytes).
- **`cd <dir_name>`**: Change the current directory.
- **`rm <file_name>`**: Remove a file and send it to the virtual bin.
- **`size <file_name>`**: Display the size of a file.
- **`showbin`**: Display the contents of the virtual bin.
- **`emptybin`**: Permanently clear the virtual bin.

### Additional Commands
- **`find <file_name>`**: Search for files by name across the directory structure.
- **`mv <src> <dst>`**: Move or rename files and directories.
- **`recover`**: Recover deleted files from the virtual bin.
- **`clear`**: Clear the console screen.
- **`exit`**: Exit the VFS program.

## Usage
![Assignment 111](https://github.com/user-attachments/assets/bb4d3ed1-bc8c-42a6-9b59-300044439f6b)


## Installation and Setup

### Clone the repository:
```bash
git clone https://github.com/ReginaldKotey/VFS.git
cd VFS
//cd into MacOs or Windows Respectively
make
./run
```
## Makefile

The project includes a `Makefile` to streamline the build process. Use the following commands:

- **`make`**: Compiles the project and generates the executable `run`.
- **`make clean`**: Cleans the build by removing the generated files.

## Why VFS?

VFS provides a lightweight and intuitive interface for file and directory management. It is ideal for:

- **Learning purposes**: Explore file system commands in a safe virtual environment.
- **Simulations**: Practice file recovery and directory navigation with ease.
- **Customization**: Extend and adapt the system to simulate more complex file operations.

## Future Enhancements

- **User access management**: Implement user-specific permissions and roles.
- **File compression**: Support file compression and decompression.
- **Network functionality**: Allow sharing files between different instances of VFS.

## Contributing

Contributions are welcome! Feel free to fork the repository, submit pull requests, or open issues for any bugs or feature requests.


## License

    Copyright [2024] [Reginald Kotey Appiah-Sekyere]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

