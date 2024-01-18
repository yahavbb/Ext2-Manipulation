# Ext2 File System Manipulation

## Introduction

Welcome to the Ext2 Manipulation project! This tool is designed for interacting with Ext2 file systems, primarily used in Unix-like operating systems. It's an invaluable resource for understanding and managing Ext2 file systems, whether you're a student, a developer, or just a tech enthusiast.

## Features

- **Superblock and Group Descriptor Analysis**: Easily locate and read superblocks and group descriptors.
- **Inode and Directory Entry Exploration**: Access and examine inodes and directory entries in detail.
- **File System Component Printing**: Print critical information about file system components for easy analysis.
- **Permission Management**: Effortlessly change file permissions within the Ext2 file system.

## Getting Started

### Prerequisites

- A C compiler (like GCC)
- A Unix-like operating system (Linux is ideal)

### Building

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yahavbb/Ext2-Manipulation.git
   cd Ext2-Manipulation
   ```

2. **Compile the Code**:
   ```sh
   make
   ```

### Usage

Execute the program with suitable arguments to perform various operations:

```sh
./ext2_tool <virtual_disk> <file_path> <operation> <permission>
```

- `virtual_disk`: Path to the virtual disk image of the Ext2 file system.
- `file_path`: Path to the target file or directory within the file system.
- `operation`: The desired operation (e.g., `print`, `chmod`).
- `permission`: For `chmod`, specify the permission in octal format.

## Usage Examples

Here are some practical examples:

1. **Print Superblock and Group Descriptor Info**:
   ```sh
   ./ext2_tool disk.img /some/file/path print
   ```

2. **Display File Contents**:
   ```sh
   ./ext2_tool disk.img /path/to/file.txt print
   ```

3. **Change File Permission**:
   ```sh
   ./ext2_tool disk.img /path/to/file.txt chmod 644
   ```

## Contributing

Your contributions make this project better! Feel free to submit pull requests or report issues. Let's make this tool more powerful together!

## Note

- This project is for educational and research purposes. Please use it responsibly.
- Any misuse for illegal activities is strongly discouraged and against the project's ethical guidelines.

## About the Author

This project was passionately crafted by Yahav Breslav. Connect with me on [LinkedIn](https://www.linkedin.com/in/yahav-breslav-bitton/) or visit my [GitHub](https://github.com/yahavbb) for more exciting projects.

---

Feel free to use or modify this enhanced README to better suit your project's needs!
