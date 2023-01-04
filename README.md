# R/W Performance

run1.c

This program can read and write a file from disk using the standard C/C++ library's `open`, `read`, `write`, and `close` functions.

Way to execute: 
`./run <filename> [-r|-w] <block_size> <block_count>` 

Expected output: 

For write (-w flag) a new file will be created with name as <filename>. 
The content written to the file will be a randomly generated digit and the size of the file will be block_size * block_count bytes.  

Prints: 
Seconds Elapsed
MBs Written
The performance of write in MBs/sec.

For read (-r flag) the code will read a file from the start and the number of bytes read should be equal to block_size * block_count. 
Will XOR the content read and print it to the terminal. Along with the XOR value will print the performance in MiB/s or bytes/sec.

Prints:
XOR Hexidecimal for the corresponding file
Seconds Elapsed
MB's Read
Amount of System Calls
The performance of read in MBs/sec.


run2.c

This program can read from disk using the standard C/C++ library's `open`, `read`, `write`, and `close` functions but does it does it much quicker with chunking.

Way to execute: 
./run2 <filename> <block_size>  

For read (-r flag) the code will read a file from the start and the number of bytes read should be equal to the filesize, with buffersize equal to block_size. 
Will XOR the content read and print it to the terminal. Along with the XOR value will print the performance in MiB/s or bytes/sec.

Prints:
XOR Hexidecimal for the corresponding file
Seconds Elapsed
MB's Read
Amount of System Calls
The performance of read in MBs/sec.
