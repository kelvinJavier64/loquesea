# loquesea

[![Languages](https://img.shields.io/github/languages/top/kelvinJavier64/loquesea)](https://github.com/kelvinJavier64/loquesea)
[![License](https://img.shields.io/github/license/kelvinJavier64/loquesea)](LICENSE)

loquesea is a C++ expert system rule interpreter.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

loquesea is a C++ project for interpreting rule-based expert systems. Rules and states are read from text files and evaluated using an AST-based interpreter.

## Features
- Written in modern C++
- Build system based on CMake
- Tokenizes, parses, and interprets custom rule/logic syntax
- Prints parse trees, detected facts, conflicts, and redundancies

## Getting Started

**Prerequisites:**
- C++ compiler (supporting C++17 or newer)
- CMake (version 3.10 or higher)
- Git

Clone the repository:
```sh
git clone https://github.com/kelvinJavier64/loquesea.git
cd loquesea
mkdir build
cd build
cmake ..
make
```

## Usage

### 1. Prepare Initial State and Rules Files
Before building and running, you need two files:
- `initState.ini`: describes initial variables and facts.
- `rules.src`: contains the rules for your system.

**Example `initState.ini`:**
```
[variables]
x = 5

[facts]
fact1 = true
fact2 = false
```

**Example `rules.src`:**
```
rule r1 : if x > 3 AND fact1 then res1
rule r2 : if x < 10 then res2
```

### 2. Build the Program
Make sure you have a C++17 compiler and CMake installed, then run:
```sh
git clone https://github.com/kelvinJavier64/loquesea.git
cd loquesea
mkdir build
cd build
cmake ..
make
```
The executable will be named `Interprete`.

### 3. Run the Program
Make sure your `initState.ini` and `rules.src` files are in the same directory as the executable or use the default names.

Run:
```sh
./Interprete
```

On startup you are prompted:
```
Read source code from rules.src? (T/F)
```
* Type `T` (or `t`) to load rules from `rules.src`.
* Type `F` (or `f`) to input rules from terminal (end input with `$`).

### 4. Program Output
The program will:
- Tokenize and parse your rules
- Build and print the Abstract Syntax Tree (AST)
- Display the initial state (variables and facts)
- Interpret your rules
- Output which facts are activated, and information about conflicts/redundancies/inactive rules

### 5. End Program
When execution finishes, press Enter to close.

## Contributing
Contributions are welcome! Please open issues and submit pull requests for any improvements or bug fixes.

## License
This project is licensed under the terms of the [LICENSE](LICENSE) file.
