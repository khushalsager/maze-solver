// Maze solver using Breadth-First Search (finds the shortest path).
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct Point { int r, c; };

std::vector<std::string> defaultMaze() {
    return {
        "##########",
        "#S..#....#",
        "#.#.#.##.#",
        "#.#...#..#",
        "#.#####.##",
        "#.....#..#",
        "#####.#.##",
        "#.....#..E",
        "##########",
    };
}

bool solve(std::vector<std::string>& maze, int& steps) {
    int R = maze.size(), C = maze[0].size();
    Point start{-1, -1}, end{-1, -1};
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (maze[r][c] == 'S') start = {r, c};
            if (maze[r][c] == 'E') end = {r, c};
        }
    if (start.r < 0 || end.r < 0) return false;

    std::vector<std::vector<Point>> parent(R, std::vector<Point>(C, {-1, -1}));
    std::vector<std::vector<bool>> seen(R, std::vector<bool>(C, false));
    std::queue<Point> q;
    q.push(start);
    seen[start.r][start.c] = true;
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};

    while (!q.empty()) {
        Point p = q.front(); q.pop();
        if (p.r == end.r && p.c == end.c) {
            steps = 0;
            for (Point cur = parent[end.r][end.c]; !(cur.r == start.r && cur.c == start.c);
                 cur = parent[cur.r][cur.c]) {
                maze[cur.r][cur.c] = '*';
            }
            Point cur = end;
            while (!(cur.r == start.r && cur.c == start.c)) { cur = parent[cur.r][cur.c]; steps++; }
            return true;
        }
        for (int i = 0; i < 4; i++) {
            int nr = p.r + dr[i], nc = p.c + dc[i];
            if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue;
            if (maze[nr][nc] == '#' || seen[nr][nc]) continue;
            seen[nr][nc] = true;
            parent[nr][nc] = p;
            q.push({nr, nc});
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> maze;
    if (argc > 1) {
        std::ifstream f(argv[1]);
        if (!f) { std::cerr << "Cannot open " << argv[1] << "\n"; return 1; }
        std::string line;
        while (std::getline(f, line)) if (!line.empty()) maze.push_back(line);
    } else {
        maze = defaultMaze();
    }
    if (maze.empty()) { std::cerr << "Empty maze\n"; return 1; }

    int steps = 0;
    if (solve(maze, steps)) {
        std::cout << "Shortest path found in " << steps << " steps:\n\n";
    } else {
        std::cout << "No path exists.\n\n";
    }
    for (const auto& row : maze) std::cout << row << "\n";
    return 0;
}
