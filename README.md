# MyCat

A simple implementation of the Unix `cat` command written in C.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))

## Features

- Display file contents
- Line numbering (`-n`)
- Number non-blank lines (`-b`)
- Squeeze blank lines (`-s`)
- Show line endings (`-E`)
- Help (`--help`, `-h`)

## Build

```bash
git clone git@github.com:AbdullahAbdelaziz122/MyCat.git
cd MyCat
make
```

**Manual build:**
```bash
gcc -Wall -Wextra -std=c99 -Isrc -o mycat src/*.c
```

**Clean:**
```bash
make clean
```

## Usage

```bash
./mycat [OPTIONS] [FILE...]
```

## Options

| Option | Description |
|--------|-------------|
| `-n`   | Number all lines |
| `-b`   | Number non-blank lines only |
| `-s`   | Squeeze multiple blank lines into one |
| `-E`   | Show `$` at line endings |
| `-h`, `--help` | Show help |

Options can be combined: `-nE`, `-n -E`, `-nEs`

## Examples

```bash
./mycat file.txt
./mycat -n file.txt
./mycat -nE file1 file2
./mycat --help
```

## Project Structure

```
MyCat/
├── src/
│   ├── main.c          # Entry point
│   ├── arguments.c     # Argument parsing
│   ├── file_io.c       # File reading/printing
│   └── mycat.h         # Shared declarations
├── Makefile
├── .clang-format
├── .gitignore
├── LICENSE
└── README.md
```

## License

MIT License - see [LICENSE](LICENSE) file.

## Acknowledgments

Inspired by the original Unix `cat` command (1971, AT&T Bell Labs).
```
