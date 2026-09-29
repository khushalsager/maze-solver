# 🧭 Maze Solver (C++)

Finds the **shortest path** through a text-based maze using Breadth-First Search (BFS).

## Requirements
- A C++11 (or newer) compiler such as `g++` or `clang++`

## Build & run
```bash
g++ -std=c++17 -Wall -Wextra -o maze_solver maze_solver.cpp
./maze_solver              # built-in sample maze
./maze_solver mymaze.txt   # your own maze file
```

## Maze format
| Char | Meaning |
|------|---------|
| `#`  | Wall |
| `.`  | Open path |
| `S`  | Start |
| `E`  | End |

The solution is drawn with `*`.

### Example output
```
Shortest path found in 20 steps:

##########
#S..#....#
#.#*#*##*#
#.#***#**#
...
```

## How it works
BFS explores the grid layer by layer from `S`, storing each cell's parent. Once `E` is reached, the path is reconstructed by walking parents backward. Because every step costs the same, BFS guarantees the shortest route.

## License
MIT
