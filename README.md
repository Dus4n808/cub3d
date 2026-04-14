*This project has been created as part of the 42 curriculum by dufama, lubaroni.*

# cub3D — My first RayCaster with miniLibX

## Description

cub3D is a Wolfenstein 3D-inspired first-person raycaster built in C using the miniLibX graphics library. The engine renders a navigable 3D maze from a 2D grid map using the DDA (Digital Differential Analysis) raycasting algorithm.

Key features:
- First-person 3D rendering with directional wall textures (North, South, East, West)
- Solid floor and ceiling colors
- Smooth player movement (WASD) and rotation (arrow keys)
- Robust `.cub` scene file parser with full error handling
- Flood-fill map closure validation
- Cross-platform support (macOS and Linux)

## Instructions

### Dependencies

- **macOS**: Xcode command line tools (for OpenGL/AppKit frameworks)
- **Linux**: `libX11-dev`, `libXext-dev`

The repository expects the following directories alongside the source:
```
libft/        — your libft
mlx-mac/      — miniLibX for macOS
mlx-linux/    — miniLibX for Linux
```

### Compilation

```bash
make          # build cub3d
make clean    # remove object files
make fclean   # remove objects + binary
make re       # fclean + build
```

### Usage

```bash
./cub3d maps/your_map.cub
```

The scene file must have the `.cub` extension and follow this format:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100N01
100001
111111
```

**Map rules:**
- Valid characters: `0` (floor), `1` (wall), `N/S/E/W` (player start + orientation)
- Map must be fully enclosed by walls
- Exactly one player spawn point

**Controls:**

| Key | Action |
|---|---|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera |
| `ESC` | Quit |
| Window ✕ | Quit |

## Resources

### Raycasting & math
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — primary reference for DDA algorithm, texture mapping, and fisheye correction
- [3DSage YouTube series](https://www.youtube.com/watch?v=gYRrGTC7GtA) — visual walkthrough of raycasting from scratch
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — MLX API reference

### AI usage

Claude (Anthropic) was used during this project for:
- **Testing**: reviewing possible issues with edge cases.
- **Documentation**: generating this README

All AI-generated suggestions were reviewed, tested, and understood before integration.
