

# ext2 File System Manipulation

A C program for interacting with ext2 file systems, implementing various operations such as reading superblocks, group descriptors, inodes, and directory entries, as well as changing permissions and printing file contents.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
  - [Usage](#usage)
- [Usage Examples](#usage-examples)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project contains C code for working with the ext2 file system, a popular filesystem format used in Unix-like operating systems. The code provides functions to perform various tasks such as locating important file system components, reading file contents, changing permissions, and more.

## Features

- Find and read superblocks, group descriptors, inodes, and directory entries
- Print information about file system components
- Change permissions of files

## Getting Started

### Prerequisites

To compile and run this code, you need:

- A C compiler (e.g., GCC)
- A Unix-like environment (Linux preferred)

### Building

1. Clone the repository:

   ```sh
   git clone https://github.com/yahavbb/Ext2-Manipulation.git
   Ext2-Manipulation
   ```

2. Compile the code:

   ```sh
   make 
   ```

### Usage

Run the compiled program with appropriate arguments to perform different operations on ext2 file systems.

```sh
./ext2_tool <virtual_disk> <file_path> <operation> <permission>
```

- `virtual_disk`: Path to the virtual disk image of the ext2 file system.
- `file_path`: Path to the file or directory within the ext2 file system.
- `operation`: Specify the operation to perform (e.g., `print`, `chmod`).
- `permission`: For the `chmod` operation, provide the desired permission in octal format.

## Usage Examples

Here are a few examples of how to use the `ext2_tool` program:

1. Print information about the superblock and group descriptor:

   ```sh
   ./ext2_tool disk.img /some/file/path print
   ```

2. Print the contents of a file:

   ```sh
   ./ext2_tool disk.img /path/to/file.txt print
   ```

3. Change the permission of a file:

   ```sh
   ./ext2_tool disk.img /path/to/file.txt chmod 644
   ```

## Contributing

Contributions are welcome! If you find any issues or want to enhance the project, feel free to submit a pull request.

