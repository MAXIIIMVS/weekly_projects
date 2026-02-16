# Analog Clock (C11, Raylib)

A simple **analog clock** written in **C11** using the **Raylib** library.
It displays the current local time with hour, minute, and second hands in a visually clean and minimal style.

No engines. No frameworks. Just **C + Raylib** doing what they do best.

## Features

- Local time display with hour, minute, and second hands
- Smooth anti-aliased clock face
- Configurable colors and sizes
- CPU-friendly update with `SetTargetFPS`
- Single-file, self-contained C project

## Quick Start

### Prerequisites

- **C compiler** supporting C11 (GCC, Clang recommended)
- **CMake** 3.16+
- **Raylib** 5.5 (will be automatically fetched if missing)
- Unix-like or Windows environment supported by Raylib

### Build with CMake

```bash
mkdir build
cmake -S . -B ./build
cmake --build ./build
```

The executable `main` will be created in the build folder.

### Run

```bash
.build/main
```

On Windows:

```cmd
./build/main.exe
```

## Usage

- Clock updates every second (FPS can be configured via `SetTargetFPS`)
- Hour, minute, and second hands are drawn with different colors and thickness
- Minute marks highlight each 5-minute interval
- Anti-aliasing enabled for smooth visuals

### Controls

- Close the window normally to exit
- Supports window resizing (clock scales with window size)

## Notes

- Uses `SetTargetFPS` to throttle drawing, keeping CPU usage minimal
- Second-hand “tick” can be made smoother by increasing FPS
- Thread-safe `localtime_r` used to get current local time

## Possible Improvements

- Add hour numbers (1–12) on the clock face
- Implement smooth sweeping second-hand instead of tick
- Dynamic color themes
- Add digital time overlay
- Cross-platform packaging (Windows, Linux, macOS)

---

This project is meant to be **lightweight, simple, and educational**.
If it breaks, blame the time — not the code. 😄
