# Minishell Project

Welcome to my **Minishell** project, a deep dive into the heart of Unix-based command-line interfaces. This repository showcases my journey through building a miniature version of the Bash shell as part of the 42 School curriculum.

## Overview
Minishell is a simplified shell implementation written in C. Its goal is to replicate essential Bash functionalities while teaching core concepts like process management, memory allocation, system calls, and parsing techniques.

## Key Features
- **Command Execution:** Supports built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Redirections & Pipes:** Handles input/output redirection and pipelines like `ls | grep file > output.txt`.
- **Environment Management:** Manages environment variables dynamically.
- **Signal Handling:** Responds gracefully to signals like `Ctrl+C` and `Ctrl+D`.
- **Custom Parsing:** Tokenizes and processes user input for seamless command execution.

## My Role
I focused on:
- **Parsing:** Converting raw user input into executable command structures.
- **Built-ins Implementation:** Writing and optimizing core shell commands.
- **Memory Management:** Debugging memory leaks and ensuring efficient resource use.

## Challenges & Lessons Learned
- **System Calls Mastery:** Leveraging `fork`, `execve`, and `pipe` for process control.
- **Error Handling:** Managing unexpected input and edge cases.
- **Norminette Compliance:** Following strict C coding standards for clean, maintainable code.

## Why This Project Matters
Working on Minishell has deepened my understanding of operating systems, process management, and shell functionality. It’s more than just a project — it’s a hands-on exploration of how Unix systems operate under the hood.

## How to Use
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/minishell.git
   ```
2. Compile the source code:
   ```bash
   make
   ```
3. Run the shell:
   ```bash
   ./minishell
   ```

## What’s Next?
While I completed the core features, there’s always room for improvement. Future goals include implementing logical operators like `&&` and `||`, enhancing error handling, and refining built-in commands.

## Acknowledgments
Special thanks to my teammate for tackling command execution and system calls. This project was an intense but rewarding experience, blending theory and practice in low-level programming.

Happy coding! 🚀

