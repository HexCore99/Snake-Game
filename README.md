# Snake Game

A classic Snake game implementation built with C++ and Raylib graphics library.

## Description

This is a modern take on the classic Snake game where you control a snake that grows longer as it eats food. The game features smooth animations and collision detection to provide an engaging gameplay experience.

## Features

- **Smooth Movement**: Physics-based snake movement with fluid animations
- **Growing Mechanic**: Snake grows longer each time it eats food
- **Collision Detection**: Boundary checking and self-collision prevention
- **Random Food Spawning**: Food appears at random positions on the screen
- **Visual Feedback**: Distinct colors for snake head (white), body (brown), and food (red)

## Requirements

- C++ Compiler (g++)
- Raylib library
- Windows (current Makefile is configured for Windows with MSYS2)
- OpenGL, GDI32, and WinMM libraries

## Installation

### Prerequisites

1. Install MSYS2 (for Windows)
2. Install Raylib library:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-raylib
   ```

### Clone the Repository

```bash
git clone https://github.com/HexCore99/Snake-Game.git
cd Snake-Game
```

## Building the Game

Use the provided Makefile to build the game:

```bash
make build
```

This will compile `main.cpp` and create the `main.exe` executable.

## Running the Game

To build and run the game in one command:

```bash
make run
```

Or run the executable directly:

```bash
./main.exe
```

## How to Play

- The snake starts in the center of the screen moving to the right
- Red rectangles appear randomly on the screen - these are the food
- Guide the snake to eat the food to grow longer
- Avoid hitting the boundaries of the screen
- Try to grow your snake as long as possible!

## Controls

- **W** - Move Up
- **A** - Move Left
- **S** - Move Down
- **D** - Move Right

## Game Settings

- Screen Resolution: 1200x800 pixels
- Target FPS: 60
- Snake Block Size: 30x30 pixels
- Initial Snake Length: 8 segments

## Cleaning Up

To remove the compiled executable:

```bash
make clean
```

## Technical Details

The game is built using:
- **Raylib**: A simple and easy-to-use library for game development
- **C++ STL**: Uses `deque` for efficient snake body management
- **Vector Mathematics**: For smooth movement and collision calculations

## License

This project is open source and available for educational purposes.

## Credits

Developed by HexCore99
