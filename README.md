# Space Invaders

A Space Invaders clone written in C using SDL3.

## Dependencies

- SDL3
- SDL3_image
- SDL3_ttf
- CMake 3.16+

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

From the build directory:

```bash
./space_invaders
```

Assets are expected to be located at `../assets/` relative to the executable.

## Controls

| Key | Action |
|-----|--------|
| Arrow Left | Move left |
| Arrow Right | Move right |
| Space | Fire |
| Enter | Start game |
| R | Restart after game over |
| Escape | Quit |

## Gameplay

Shoot down all the enemies before they reach you. Enemies speed up as their numbers decrease. The game ends if any enemy reaches the player's row.

### Scoring

| Enemy | Points |
|-------|--------|
| Red (top row, 3 HP) | 30 |
| Yellow (middle row, 2 HP) | 20 |
| Green (bottom row, 1 HP) | 10 |

