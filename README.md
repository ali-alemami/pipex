*This project has been created as part of the 42 curriculum by aalemami.*

# pipex

---

## Description

pipex is a Unix process management project that replicates the behavior of the shell pipe operator. It takes an input file, two commands, and an output file, chaining them together exactly as the shell does with `<` and `>` redirections and `|`.

The goal is to understand how processes communicate through pipes using `fork()`, `pipe()`, `dup2()`, and `execve()`, and to properly handle file descriptors, child process synchronization, PATH resolution, and resource cleanup.

---

## Instructions

### Compilation

Initialize submodules and compile using `make`:

```bash
git submodule update --init
make
```

Additional rules:
```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Rebuild from scratch
```

### Usage

```bash
./pipex <infile> <cmd1> [flags] <cmd2> [flags] ... <outfile>
```

| Argument | Description |
| :--- | :--- |
| `infile` | File to read input from |
| `cmd` | Command executable (resolved via PATH) |
| `flags` | Optional command flags (e.g. `-l`, `-n`) |
| `outfile` | File to write final output to |

Equivalent shell behavior:
```bash
< infile cmd1 | cmd2 > outfile
```

### Examples

```bash
./pipex infile ls -l wc -l outfile
./pipex infile head -5 wc -c outfile
```

Multiple commands can be chained in sequence:
```bash
./pipex infile cat -n head -3 wc -l outfile
```

---

## Resources

- [pipe(2) — Linux man page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [fork(2) — Linux man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [execve(2) — Linux man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [dup2(2) — Linux man page](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [Unix Processes in C — CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

### AI Usage

AI was used as a learning and reference tool for:
- Understanding file descriptor duplication mechanics with `dup2()`.
- Clarifying process execution workflows with `execve()` and environment `PATH` parsing.
- Debugging exit status propagation and zombie process prevention via `waitpid()`.