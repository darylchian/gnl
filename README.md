*This project has been created as part of the 42 curriculum by tchian.*

# Get Next Line

## Description

Get Next Line is a C project that implements `char *get_next_line(int fd)`.
Each call returns the next line read from a file descriptor. The returned line
includes its terminating newline when one is present. At end-of-file, the
function can return a final line that does not end in `\n`; it returns `NULL`
when no more line is available or when an error occurs.

The project helps develop an understanding of file handling, static variables, dynamic memory allocation, and buffer management in C.

The function prototype is:

char *get_next_line(int fd);

Each call returns the next line, including the newline character (\n) when present. When there is nothing left to read, or an error occurs, the function returns NULL.

## Files

- `get_next_line.c`: reading, persistent saved data, and line extraction.
- `get_next_line_utils.c`: string helper functions.
- `get_next_line.h`: function declarations and default `BUFFER_SIZE`.
- `main.c`: optional command-line test program.
- `Makefile`: builds a static library or the test program.

## Instructions

Build the library:

```sh
make
```

This creates `libgnl.a`.

Build the test program:

```sh
make test
```

Run it against a text file:

```sh
./gnl_test test.txt
```

Try different buffer sizes:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c 
get_next_line_utils.c main.c -o gnl\

```

The source also defines a default `BUFFER_SIZE` of 42 when no compile-time
value is supplied.

Clean generated files:

```sh
make clean
make fclean
make re
```

## Algorithm

1. Read to remainder: Read data from the file descriptor until a newline or end-of-file is encountered. Store the data in a persistent buffer.

2. Extract line: Extract the first complete line from the stored data, including the newline character if present.

3. Clean remainder: Remove the extracted line while preserving unread characters for the next function call.

4. Return line: Return the extracted line to the caller, who is responsible for freeing its memory.

A static variable preserves the remaining data between function calls.

## Testing checklist

Test at least these cases:

- Empty file.
- One line ending in `\n`.
- One line without a final `\n`.
- Multiple lines.
- Blank lines.
- A buffer size of 1.
- A buffer size larger than the input.
- Invalid file descriptor.
- Reading from standard input.
- Memory leaks (e.g., with valgrind).

## Resources

- The supplied Get Next Line subject, version 14.3.
- `man 2 read`, `man 2 open`, and `man 3 malloc`.
- 42 project instructions and peer evaluation.
- Peer learning discussions and test programs from other students.

The following resources are useful for understanding the concepts involved:

man 2 read — Documentation for the read() system call.

man 3 malloc — Dynamic memory allocation.

man 3 free — Memory deallocation.

42 Norminette — Coding style checker.

GNU C Library Manual — Reference for C programming.

AI usage
AI assistance was used to assemble this starter implementation, explain the project
structure, and prepare the Makefile and README. The author reviewed the code, studied each
helper function, and tested the behavior before submission. AI was not used to replace
understanding of the algorithm; it was used as a drafting and documentation aid.
