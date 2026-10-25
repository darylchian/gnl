*This project has been created as part of the 42 curriculum by tchian.*

# Get Next Line

## Description

Get Next Line is a C project that implements `char *get_next_line(int fd)`.
Each call returns the next line read from a file descriptor. The returned line
includes its terminating newline when one is present. At end-of-file, the
function can return a final line that does not end in `\n`; it returns `NULL`
when no more line is available or when an error occurs.

This package follows the mandatory part of the supplied Get Next Line subject
(version 14.3). It includes a small `main.c` test program, which is for local
testing and is not part of the mandatory submission files.

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
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
  get_next_line.c get_next_line_utils.c main.c -o gnl_test
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

1. Allocate a read buffer of `BUFFER_SIZE + 1` bytes on the stack.
2. Read from the supplied file descriptor until a newline is found or `read`
   reaches end-of-file.
3. Append each read chunk to a static saved string. The static variable
   retains unread data between calls without using a global variable.
4. Extract the first line, including `\n` if present.
5. Keep the remaining text for the next call.
6. Return `NULL` when no line remains or if an error/allocation failure occurs.


The function uses `read`, `malloc`, and `free`. It does not use `lseek`,
libft, or global variables. The mandatory implementation keeps one static
saved string and is intended for one file descriptor at a time; simultaneous
interleaved descriptors are part of the subject's bonus requirements.

Detailed explanation
The static variable stash (called stash in get_next_line.c) is the persistent state.
It holds bytes that have been read from the file descriptor but not yet returned as part
of a line. Because it is static, its value survives between calls to get_next_line without
using a global variable, which is forbidden.

fill_stash is responsible for reading. It loops while ft_strchr(stash, '\n') returns NULL,
meaning the stash does not yet contain a complete line. Inside the loop it calls read(fd,
buffer, BUFFER_SIZE). The return value bytes tells how many bytes were actually copied
into buffer. A return of 0 means end of file; a negative value means an error. In either
case the loop breaks. Otherwise, buffer[bytes] = '\0' terminates the raw bytes so that
string helpers can operate safely. The new chunk is joined to the existing stash with
ft_strjoin. If ft_strjoin fails, the old stash is freed and NULL is returned. On success,
the old stash is freed and replaced by the joined result. This avoids memory leaks and
keeps the stash as a single dynamically allocated C string.

make_line extracts the line to return. It searches for '\n' in the stash. If no newline
exists, it duplicates the entire stash with ft_strdup and returns that copy. If a newline
exists, it temporarily replaces the character after the newline with '\0', duplicates the
stash up to and including the newline, then restores the original character. This produces
a standalone line string that the caller can use and free independently.

leftover builds the new stash. It finds the newline, and if there is text after it,
duplicates that remainder with ft_strdup. If there is no newline, or the newline is the
last character, it returns NULL, meaning no leftover data remains. The caller then free
the old stash and assigns the leftover as the new stash.

Finally, get_next_line validates fd and BUFFER_SIZE, calls fill_stash, checks for an empty
the leftover, and returns the line. If the stash is empty or fill_stash failed, it free
the stash, sets it to NULL, and returns NULL.

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

AI usage
AI assistance was used to assemble this starter implementation, explain the project
structure, and prepare the Makefile and README. The author reviewed the code, studied each
helper function, and tested the behavior before submission. AI was not used to replace
understanding of the algorithm; it was used as a drafting and documentation aid.
