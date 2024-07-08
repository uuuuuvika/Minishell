# Minishell Project README

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Commands](#commands)
6. [Contributing](#contributing)
7. [License](#license)
8. [Contact](#contact)

## Introduction

Minishell is a simple, minimalist shell designed to provide basic command-line interface functionality. It is a smaller, educational version of a Unix shell like `bash` or `zsh`, created to help understand how shells operate, manage processes, and handle user input.

## Features

- Basic command execution (e.g., `ls`, `echo`, `pwd`)
- Handling of built-in shell commands (`cd`, `echo`, `exit`, `export`, `pwd` `unset`)
- Input and output redirection (`>`, `<`, `>>`, `<<`)
- Pipelining with `|`
- Environment variable handling and expansions
- Signal handling (e.g., `Ctrl+C` to terminate a running command and `Ctrl+D`)

## Installation

To install and set up Minishell, follow these steps:

1. **Clone the repository:**

    ```bash
    git clone https://github.com/yourusername/minishell.git
    cd minishell
    ```

2. **Build the project:**

    ```bash
    make m
    ```

    This will compile the source code and run the executable named `minishell`.

## Usage

To start using Minishell, run the following command in your terminal:

```bash
./minishell
```

You will be greeted with a prompt where you can start typing commands.

## Commands

Minishell supports a variety of commands, including both built-in commands and external commands available in your system's PATH.

### Built-in Commands
```
    cd [directory]: Change the current directory to directory.
        cd ..: Move to the parent directory.
        cd ~: Move to the home directory.
        cd .: Stay in the current directory.
```
```
    exit [status]: Exit the shell with an optional exit status.
```
```
    echo [string]: Print string to the terminal.
        echo -n [string]: Print string without a trailing newline.
```
```
    env: Print all environment variables.
```
```
    export [var]=[value]: Set an environment variable var to value.
```
```
    unset [var]: Remove the environment variable var.
```

### External Commands

Any executable found in the directories listed in the `PATH` environment variable can be executed. For example:

- `ls -la`
- `grep "pattern" file.txt`

### Redirection

- **Output Redirection**: Use `>` to redirect output to a file.

    ```minishell
    echo "Hello, World!" > hello.txt

    ```
- **Append Output Redirection**: Use `>>` to redirect output to a file, appending to the file if it exists.

    ```minishell
    echo "Hello, again!" >> hello.txt
    ```

- **Input Redirection**: Use `<` to redirect input from a file.

    ```minishell
    cat < hello.txt
    ```

- **Here Document**: Use `<<` to redirect input from a string until a delimiter is found.

    ```minishell
    cat << EOF
    Hello, World!
    EOF
    ```

### Pipelining

Use `|` to pipe the output of one command as the input to another.

```bash
ls -la | grep "pattern"
```

This Minishell is a project of the 42 Berlin curriculum designed and written in collaboration by /uuuuuvika and /ProjectDaiana

For any questions or suggestions, please feel free to open an issue or contact the project maintainers.

Happy coding!
