# HotRace - Fast Key-Value Search Engine

## Overview
A C implementation of a high-speed key-value storage and retrieval system, designed as part of a programming competition focusing on algorithm optimization.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Compilation](#compilation)
- [Project Rules](#project-rules)
- [Submission](#submission)
- [Performance Tips](#performance-tips)

## Features
- Lightning-fast key-value storage and retrieval
- Simple stdin/stdout interface
- Graceful handling of missing keys
- Optimized for performance (critical for grading)

## Requirements
- C compiler (gcc/clang)
- GNU Make
- Compliance with project Norm (coding style)

## Installation
```bash
git clone https://github.com/houdaifa-boukhari/Hotrace.git
cd Hotrace
make
```

## Usage
1. Run the compiled program:
```bash
./hotrace
```

2. Input format:
```
# Storage phase
key1
value1
key2
value2
[empty line marks end of storage]
# Search phase
search_key1
search_key2
```

3. End input with Ctrl+D (EOF)

## Examples

### Basic Example
Input:
```
apple
red fruit
banana
yellow fruit

apple
banana
pear
```

Output:
```
red fruit
yellow fruit
pear: Not found.
```

### File Input Example
```bash
./hotrace < data.txt
```

## Compilation
- Compiled with strict flags: `-Wall -Wextra -Werror`
- Makefile targets:
  - `all`: Compile project
  - `clean`: Remove object files
  - `fclean`: Full clean
  - `re`: Rebuild project

## Project Rules

### Allowed Functions
```c
read(), write(), malloc(), free(), strerror()
```
- `__asm__` directive permitted
- No external libraries (including libft)

### Critical Requirements
- No memory leaks
- No crashes (segfaults, bus errors, etc.)
- Must handle undefined behavior gracefully
- Performance is key grading factor

## Submission
- Repository must contain:
  - All source files at root
  - Working Makefile
  - Program named `hotrace`
- Do NOT include test programs

## Performance Tips
- Optimize your search algorithm (consider hash tables)
- Minimize system calls
- Efficient memory management is crucial

---
