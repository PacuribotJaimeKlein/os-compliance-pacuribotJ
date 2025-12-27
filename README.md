# Producer-Consumer Problem in C
This project implements the classic Producer-Consumer problem using:
- POSIX threads (`pthread`)
- Semaphores (`sem_t`)
- Circular buffer of fixed siz

## Features
- Configurable number of producers and consumers.
- Buffer state printed after each operation.
- Thread-safe operations using semaphores.

## How to Run
1. Compile the code:
   ```bash
   gcc -o prod_cons prod_cons.c -pthread
