*This project has been created as part of the 42 curriculum by aalemami.*

## Description

pipex is a Unix process management project that replicates the behavior of the shell pipe operator. It takes an input file, two commands, and an output file, chaining them together exactly as the shell does with `<` and `>` redirections and `|`.

The goal is to understand how processes communicate through pipes using `fork`, `pipe`, `dup2`, and `execve`, and to handle file descriptors, PATH resolution, and memory correctly.

## Instructions

**Compilation:**

```
cd pipex
make
```

**Usage:**

```
./pipex <infile> <cmd1> <cmd2> <outfile>
```

| Argument | Description |
|----------|-------------|
| `infile` | File to read input from |
| `cmd1` | First command (reads from infile) |
| `cmd2` | Second command (writes to outfile) |
| `outfile` | File to write final output to |

Equivalent shell behavior:
```
< infile cmd1 | cmd2 > outfile
```

**Examples:**

```
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "cat" "grep hello" outfile
./pipex infile "head -5" "tr a-z A-Z" outfile
```

## Resources

- [pipe(2) — Linux man page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [fork(2) — Linux man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [execve(2) — Linux man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [dup2(2) — Linux man page](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [Unix Processes in C — CodeVault (YouTube)](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

---

**AI usage:**

Claude (claude.ai) was an invaluable resource throughout the project, providing clear and in-depth explanations that made tackling complex Unix concepts significantly easier.