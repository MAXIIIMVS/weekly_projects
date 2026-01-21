# Tic-Tac-Toe (C++23, Terminal)

A simple **terminal-based Tic-Tac-Toe game** written in **modern C++23**, using standard I/O and ANSI escape codes for screen clearing. Two players take turns entering moves until someone wins or the game ends in a draw.

No frameworks. No engines. Just C++ doing C++ things.

## Features

- Two-player local gameplay
- Clean terminal UI with board redraws
- Input validation (invalid numbers, occupied cells)
- Win detection (rows, columns, diagonals)
- Draw detection
- Graceful handling of end-of-file input (`Ctrl-D`)
- Uses modern C++23 features (`<print>`)

## Quick Start

### Prerequisites

- A C++ compiler with **C++23 support**
  - GCC 13+ or Clang 17+ recommended

- Unix-like terminal (Linux/macOS) for ANSI escape sequences

### Build

Compile with:

```bash
g++ -std=c++23 -Wall -Wextra -O2 -o tictactoe main.cpp
```

If your compiler needs it, you may have to link `stdc++exp` explicitly:

```bash
g++ -std=c++23 -Wall -Wextra -O2 -o tictactoe main.cpp -lstdc++exp
```

### Run

```bash
./tictactoe
```

## Usage

### Playing the Game

- Players take turns entering a number from **1 to 9**
- The numbers correspond to board positions:

```
+-----+-----+-----+
|  1  |  2  |  3  |
+-----+-----+-----+
|  4  |  5  |  6  |
+-----+-----+-----+
|  7  |  8  |  9  |
+-----+-----+-----+
```

- Player 1 uses **X**
- Player 2 uses **O**

### Invalid Input

- Non-numeric input is ignored
- Numbers outside `1–9` are rejected
- Choosing an occupied cell does nothing
- The game simply asks again (politely)

### Exiting the Game

- Press **Ctrl-D** to exit gracefully
- Press **Ctrl-C** to force quit (like a barbarian)

## Notes

- Screen clearing is done using ANSI escape codes:
  - Works in most modern terminals
  - Not guaranteed on Windows without ANSI support

- The game is intentionally simple and synchronous
- Designed as a learning exercise and a clean baseline

## Possible Improvements

- Single-player mode (AI)
- Configurable board size
- Better separation of input, logic, and rendering
- Cross-platform screen handling
- Unit tests (yes, even for Tic-Tac-Toe)

---

This project is small on purpose.
If it breaks, it’s your fault — and that’s a feature. 😄
