# minishell

**A simple shell implementation in C**

## Description

Minishell is a project that recreates the behavior of a Unix shell. This implementation provides a command-line interface that interprets and executes user commands, supporting various shell features including pipes, redirections, environment variable expansion, and built-in commands.

## Features

### Command Execution
- Execute commands from PATH or absolute/relative paths
- Support for command arguments and options
- Proper signal handling (Ctrl-C, Ctrl-D, Ctrl-\)

### Built-in Commands
- `echo` - Display text (with `-n` option support)
- `cd` - Change directory (with relative/absolute paths)
- `pwd` - Print working directory
- `export` - Set environment variables
- `unset` - Unset environment variables
- `env` - Display environment variables
- `exit` - Exit the shell

### Redirections
- `<` - Input redirection
- `>` - Output redirection (overwrite)
- `>>` - Output redirection (append)
- `<<` - Here-document (heredoc)

### Pipes
- Multiple pipes (`|`) for chaining commands
- Proper file descriptor management

### Expansion
- Environment variable expansion (`$VAR`)
- Exit status expansion (`$?`)
- Quote handling (single `'` and double `"` quotes)

### Lexical Analysis & Parsing
- Tokenization of input commands
- Syntax validation
- Command parsing and translation

## Project Structure

```
minishell/
├── includes/          # Header files
├── libft/            # Custom C library
├── srcs/             # Source files
│   ├── builtins/     # Built-in command implementations
│   ├── exec/         # Command execution logic
│   ├── expanser/     # Variable expansion handling
│   ├── lexical/      # Lexical analysis
│   ├── parsing/      # Command parsing
│   ├── token/        # Tokenization
│   └── translator/   # Command translation
├── Makefile          # Build configuration
└── README.md         # Project documentation
```

## Installation

### Prerequisites
- GCC or Clang compiler
- Make
- GNU Readline library

### Building

1. Clone the repository:
```bash
git clone https://github.com/keomalima/minishell.git
cd minishell
```

2. Compile the project:
```bash
make
```

This will compile the project with the following flags:
- `-Wall -Wextra -Werror` (strict compilation)
- `-g3` (debugging symbols)
- Links with `libft` and `readline`

3. Run minishell:
```bash
./minishell
```

## Usage

Once launched, minishell displays a prompt:
```
minishell$ 
```

You can then enter commands just like in a regular shell.

### Examples

```bash
# Basic command execution
minishell$ ls -la

# Pipes
minishell$ cat file.txt | grep "search" | wc -l

# Redirections
minishell$ echo "Hello World" > output.txt
minishell$ cat < input.txt > output.txt

# Environment variables
minishell$ export MY_VAR=hello
minishell$ echo $MY_VAR

# Built-in commands
minishell$ cd /tmp
minishell$ pwd
minishell$ env

# Exit status
minishell$ ls
minishell$ echo $?
```

## Development

### Compilation Options

```bash
make          # Compile the project
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile everything
```

### Debugging with Valgrind

```bash
make val      # Run with basic valgrind checks
make valmax   # Run with comprehensive valgrind checks (including child processes)
```

## Implementation Details

### Architecture

1. **Tokenization**: Input is split into tokens (commands, arguments, operators)
2. **Lexical Analysis**: Tokens are validated for syntax errors
3. **Parsing**: Tokens are organized into command structures
4. **Expansion**: Variables and special characters are expanded
5. **Execution**: Commands are executed with proper redirections and pipes

### Signal Handling
- `SIGINT` (Ctrl-C): Displays a new prompt
- `SIGQUIT` (Ctrl-\): Ignored in interactive mode
- `EOF` (Ctrl-D): Exits the shell

## Technical Specifications

- **Language**: C
- **Standard**: C99 with POSIX extensions
- **External Functions**: `readline`, `add_history`, `fork`, `execve`, `pipe`, `dup2`, and standard library functions
- **Memory Management**: All heap allocations are properly freed (no memory leaks)

## Authors

- **Keoma Ricci de Lima** ([keomalima](https://github.com/keomalima))
- **Ly-Sha Than** ([lyshathan](https://github.com/lyshathan))

## Acknowledgments

This project was developed as part of the 42 School curriculum, following strict coding standards and best practices.

---

*Last updated: March 2025*
