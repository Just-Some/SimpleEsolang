# What It Is and What It Is For
This is a minimalist esoteric stack-based programming language similar to Forth and False.
It has functions (words), recursion, branching, and 15 primitives. At the same time, the entire implementation fits in just 67 lines of C code!
For test run `./a.out file`.
You can find examples on this language on dir examples in repo.

# Specification

## Word
A word consists of the first byte (character) of the word's name and the rest of its body up to `\n`.
`\n` simultaneously marks the beginning of a new word and acts as the `return` for the previous one.
All words are stored in a single array and accessed using their names represented as numbers.
Words are not stored as arrays themselves, but as indices pointing to the corresponding code. This makes it possible to reduce the overall size significantly.
Words also support recursion. However, this comes with the possibility of getting a call stack overflow error.

## Primitives
| Symbol | Operation                                 |
| ------ | ----------------------------------------- |
| `p`    | Push the next program byte onto the stack |
| `?`    | Conditionally skip the next byte (`JNZ`)  |
| `$`    | `dup`                                     |
| `%`    | `drop`                                    |
| `\`    | `swap`                                    |
| `@`    | `rot`                                     |
| `>`    | Compare `y > x`                           |
| `=`    | Compare `y == x`                          |
| `&`    | Logical `AND`                             |
| `+`    | Addition                                  |
| `-`    | Subtraction                               |
| `/`    | Division                                  |
| `*`    | Multiplication                            |
| `.`    | Output a number                           |
| `,`    | Output a character                        |

## Standard Library
| Word | Operation                                                          |
| ---- | ------------------------------------------------------------------ |
| `i`  | Subtracts the ASCII code of the space character                    |
| `^`  | `over`                                                             |
| `!`  | Negation (`not`)                                                   |
| `n`  | Subtracts the ASCII code of `0` to convert a character to a number |
| `#`  | Duplicates the second-to-last element twice                        |
| `<`  | Compare `x < y`                                                    |
