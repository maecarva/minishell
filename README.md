# minishell

> "minishell" Project – École 42 Paris

## Overview

`minishell` is a minimalist command-line interpreter that replicates the core functionality of a UNIX shell. Developed as part of the 42 Paris curriculum, this project allowed us to apply fundamental concepts of lexical analysis, Abstract Syntax Tree construction, process control, and inter-process communication.

## Key Features

- **Lexical Analysis (Lexing):** Tokenizes user input into command words, operators, and redirections.
- **AST Construction:** Builds and traverses an Abstract Syntax Tree to organize commands and operators in a structured hierarchy.
- **Command Execution:** Launches external processes using `execve`, manages environment variables and PATH resolution.
- **UNIX Pipes:** Chains multiple commands with `pipe()` to redirect output from one process to another.
- **Redirections:** Supports input (`<`), output (`>`), and append (`>>`) redirections.
- **Built-in Commands:** Implements `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit` natively.

## Installation

```bash
git clone https://github.com/maecarva/minishell
cd minishell
make
```

## Usage

```bash
# Launch the shell
./minishell

# Example commands
$ echo "Hello, world!"
$ ls -l | grep README.md
$ cd src && pwd
$ cat input.txt | grep "42" > output.txt
```

## Skills Gained

- Implemented a **lexer** to convert strings into discrete tokens.
- Designed and traversed an **AST** to enforce command precedence and structure.
- Used **fork**, **execve**, **pipe**, and **dup2** for process management and I/O redirection.
- Mastered **UNIX pipes** to handle command chaining.
- Handled error cases and signal management.

## Project Structure

```plaintext
minishell/
├── src_minishell/
│	├── builtin/         		# Built-in command implementations (e.g., cd, echo)
│	├── clear/           		# Utilities for clearing and resetting shell state
│	├── init/            		# Initialization routines (environment setup, variables)
│	├── main.c           		# Entry point: reads input and drives the shell loop
│	├── move_in_ast.c    		# Functions to traverse and manipulate AST nodes
│	├── parsing/         		# Core parsing logic
│	│   ├── ast/             	# AST node definitions and constructors
│	│   ├── expander/        	# Variable and wildcard expansion
│	│   ├── lexer/           	# Tokenization modules
│	│   ├── parser/          	# Parsing modules that build the AST
│	│   ├── parsing_utils.c  	# Helper functions for parsing
│	│   ├── rules/           	# Grammar rules definitions
│	│   └── utils/           	# Parsing helper functions
│	├── pipes/          		# Pipe management and command chaining
│	├── redirection/     		# I/O redirection handlers
│	└── signals/         		# Signal handlers (e.g., SIGINT, SIGQUIT)
└── README.md          			# Project documentation
```
