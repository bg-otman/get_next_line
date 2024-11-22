# Get Next Line  

This project is part of the 1337 curriculum and focuses on implementing a function called `get_next_line` that reads a line from a file descriptor one at a time.  

## Purpose  
The goal of the project is to understand and manage:  
- File handling in C.  
- Memory management using `malloc` and `free`.  
- Buffer management for efficient reading.  
- Static variables to maintain context across multiple calls.  

## Features  
- Reads a single line from a file descriptor with each call, including the newline character (`\n`).  
- Supports reading files, standard input, or other file descriptors.  
- Handles different buffer sizes defined by `BUFFER_SIZE`.  
- Works efficiently with static variables and optimized memory usage. 

## Bonus
The bonus part extends the functionality to handle multiple file descriptors simultaneously.
