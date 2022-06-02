# Matrices Project
## Expanding knowledge of matrices by implementing in C and Rust!
### Followed markkraay's GitHub project and their [YouTube video](https://www.youtube.com/watch?v=ReOxVMxS83o&amp;t=2s) for a general set-up and then expanded on their implementation to fully incorporate all operations in linear algebra!

## C Files:

### Goals
1. Refactor the multiply method so that it has a stride of 1
2. Implement scalar multiplication
3. Implement a determinant function
4. Implement a transpose function
5. Implement an inverse function

### **matrix._** files
The matrix header and C files outline and define the functions for 
1. creating a matrix
2. printing a matrix's row and column vectors
3. filling a matrix's entries with a value
4. freeing a matrix
5. printing a matrix
6. creating a copy of a matrix
7. saving a matrix to a text file
8. loading a matrix from a text file

### **operations._** files
The operations header and C files outline and define the functions for
1. adding two matrices together
2. subtracting one matrix from another
3. matrix multiplication

### Compilation
#### The system used for compilation was the Ubuntu on Windows application (WSL)
1. To compile **matrix.c**, type the bash command `cc -g -o matrix matrix.c`
2. To compile **operations.c**, type the bash command `cc -g -o ops operations.c matrix.c -lm`

## Rust Files:

### Goals:
1. Implement a determinant function
2. Implement a transpose function
3. Implement an inverse function

### src/main.rs file
The main file contains the functions for 
1. creating a matrix,
2. printing its column and row vectors
3. printing a matrix
4. copying a matrix

The main file also contains overloaded operators for
1. adding two matrices together
2. subtracting one matrix from another
3. scalar multiplication
4. matrix multiplication

### Compilation
#### The system used for compilation was the Ubuntu on Windows application (WSL)
1. To compile the package, type the bash command "cargo build" or "cargo check"
2. To run the package, type the bash command "cargo run"
