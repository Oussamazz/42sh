***A complex shell Implementation in C programming.***

*This project is about writing the most stable and most complete UNIXshell possible.*


![bash_logo](https://bashlogo.com/img/symbol/jpg/full_colored_light.jpg)

# 42sh - My UNIX-Like Shell Implementation (C)

## Table of Contents

1. [Introduction](#introduction)
2. [Functionalities](#functionalities)
3. [Features](#features)
4. [Usage](#usage)
5. [Built-in Commands](#built-in-commands)
6. [Prompt and Exit Status](#prompt-and-exit-status)
7. [Non-Interactive Mode](#non-interactive-mode)
8. [How to Compile](#how-to-compile)
9. [Dependencies](#dependencies)

---

## Introduction

Welcome to 42sh, your implementation of a UNIX-like shell written in C. This shell project is designed to provide basic and advanced functionalities similar to the Bash shell. Feel free to explore the features and contribute to its development.

---

## Functionalities

42sh utilizes various functions and libraries to offer a comprehensive set of functionalities:

- Functions of the `terminfo` (ncurses) library
- Functions from the `man 2` section
- Memory management with `malloc` and `free`
- File and directory operations with `access`, `open`, `close`, `read`, `write`, `opendir`, `readdir`, `closedir`
- Path and directory manipulation with `getcwd`, `chdir`
- File status operations with `stat`, `lstat`
- Process management with `fork`, `execve`, `waitpid`
- Signal handling with `signal`, `kill`
- Process termination with `exit`
- Pipe operations with `pipe`
- File descriptor duplication with `dup`, `dup2`
- Terminal-related functions with `isatty`, `ioctl`, `tcsetattr`, `tcgetattr`

---

## Features

42sh comes with the following features:

- Execute basic commands
- Execute complex commands with separators, pipes, and redirections
- Manage its own environment
- Built-in commands including `cd`, `echo`, `env`, `printenv`, `pwd`, `setenv`, `unsetenv`
- Prompt based on the last exit status
- Support for non-interactive mode (running process in background/foreground)

Explore more functionalities as you dive into the shell!

---

## Usage

```bash
# Example compilation command
make
# Example execution command
./42sh [OPTIONS]
```

---

## Built-in Commands

42sh supports the following built-in commands:

- `cd` / `chdir`: Change current directory
- `echo`: Display messages
- `env`: Display or modify environment variables
- `printenv`: Display environment variables
- `pwd`: Print the current working directory
- `setenv`: Set environment variables
- `unsetenv`: Unset environment variables
...

---

## Prompt and Exit Status

The shell provides a dynamic prompt based on the last exit status, making it easier to understand the outcome of the previous command.


## How to Compile

```bash
# Example compilation command
make all
```

---

## Dependencies

Ensure you have the following dependencies installed:

- [cc/gcc, (readline)]

---
