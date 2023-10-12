# File I/O Performance Tool

## Overview

This program is a simple utility to measure the read and write performance of a file. It uses block-based operations to read or write data, allowing users to specify the size and count of blocks.
Features

    Measure read performance using specified block size and block count.
    Measure write performance by writing random data to a file using specified block size and block count.
    Display the performance in MB/s along with other metrics.

## Compilation

To compile the program, use the following command: `gcc -o io_perf_tool main.c -lpthread`

## Usage

`./io_perf_tool <file_name> -<r|w> <block_size> <block_count>`

    file_name: The path to the file you want to read or write.
    -r: To read from the specified file.
    -w: To write to the specified file.
    block_size: The size of a single block in bytes.
    block_count: The number of blocks to read/write.

## Examples

`./io_perf_tool data.bin -r 1024 100`

    Read from a file data.bin using blocks of size 1024 bytes and 100 blocks:

`./io_perf_tool data.bin -w 4096 50`

    Write to a file data.bin using blocks of size 4096 bytes and 50 blocks:

## Error Handling

In case of incorrect usage or any error during read/write operations, the program will display an error message and exit.
Note:
- The write operation generates random numbers and writes them to the file. Every 100 bytes, it inserts a newline.
- During the read operation, the program performs an XOR operation on the read data and prints the result.

## Contributing

- Please feel free to submit pull requests or raise issues to improve this tool.
