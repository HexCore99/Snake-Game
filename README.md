# Don't Be a Snake

A simple Snake game built with C++ and [raylib](https://www.raylib.com/) for Windows.

## Overview

This project is a small desktop game inspired by the classic Snake formula. The player controls a snake on a grid, collects food to grow longer, and avoids crashing into the walls or into the snake's own body.

The project currently focuses on:

- grid-based movement
- score tracking
- menu screens for start, pause, game over, and new game
- sound effects for hover, click, eating, and game over
- a standalone Windows release build

## Features

- Smooth grid movement using `W`, `A`, `S`, and `D`
- Start, resume, new game, and exit menu buttons
- Score display during gameplay
- Self-collision and wall-collision detection
- Audio feedback for menu hover, clicks, eating food, and game over
- Packaged Windows executable with required runtime DLLs

## Screenshots

### Start Screen

![Start screen](docs/screenshots/Snake_startScreen.png)

### Gameplay

![Gameplay screenshot](docs/screenshots/Snake_playing1.png)

### Gameplay With Higher Score

![Gameplay with higher score](docs/screenshots/Snake_playing2.png)

### Pause Menu

![Pause menu](docs/screenshots/Snake_pause.png)

## Controls

- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right
- `Esc` - Pause or resume the game
- `Left Mouse Button` - Click menu buttons

## Download And Run

If you are downloading a release build from GitHub Releases:

1. Download the latest Windows `.zip` file.
2. Extract the archive.
3. Make sure these items stay together in the same extracted folder:
   - `Snake.exe`
   - `assets/`
   - `libraylib.dll`
   - `libstdc++-6.dll`
   - `libgcc_s_seh-1.dll`
   - `libwinpthread-1.dll`
4. Run `Snake.exe`.

## Build From Source

### Requirements

- Windows
- [MSYS2](https://www.msys2.org/)
- UCRT64 toolchain
- `g++`
- `mingw32-make`
- `raylib`

This repository currently uses a hardcoded compiler path in the Makefile:

```make
CXX := C:/msys64/ucrt64/bin/g++.exe
```

If your MSYS2 installation is in a different location, update the Makefile before building.

### Build Commands

From the project root:

```powershell
mingw32-make clean
mingw32-make build
```

To run after building:

```powershell
.\Snake.exe
```

The current Makefile also supports:

```powershell
mingw32-make run
```

## Project Structure

```text
Snake/
  assets/               Audio files used by the game
  docs/screenshots/     README images
  main.cpp              Main game source
  Makefile              Windows build instructions
  README.md             Project documentation
```

Windows release builds also need these runtime DLLs next to the executable:

- `libraylib.dll`
- `libstdc++-6.dll`
- `libgcc_s_seh-1.dll`
- `libwinpthread-1.dll`

## How The Game Works

- The snake moves on a fixed-size grid.
- A random food point is generated on an empty tile.
- Eating food increases the score and grows the snake.
- Hitting a wall or the snake's own body ends the run.
- The menu system handles start, pause, resume, new game, and exit states.

## Release Notes

Current public release flow:

1. Build `Snake.exe`
2. Package the executable with `assets/` and the required DLLs
3. Zip the release folder
4. Upload the zip to GitHub Releases

Recommended release asset naming:

- `Snake-v1.0.1-windows.zip`

## Known Limitations

- The project is currently focused on Windows packaging.
- The build setup assumes an MSYS2 UCRT64 environment.
- There is a known future edge case to handle when the snake fills the entire board and no valid spawn tile remains for food.

## Future Improvements

- Add high score tracking
- Improve release automation
- Add a license file
- Add a CI workflow for building release artifacts automatically

## Status

This project is actively being learned through and improved iteratively.
