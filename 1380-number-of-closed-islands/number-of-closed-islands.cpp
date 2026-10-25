
class Solution {
public:
    int m, n;  // m = rows, n = columns

    // Checks whether the island is closed
    bool dfs(vector<vector<int>>& grid, int r, int c) {

        // If we go outside the grid, the island is open
        if (r < 0 || r >= m || c < 0 || c >= n)
            return false;

        // Water is safe: this direction is surrounded
        if (grid[r][c] == 1)
            return true;

        // Mark land as visited to avoid visiting it again
        grid[r][c] = 1;

        // Explore all four directions
        bool up = dfs(grid, r - 1, c);
        bool down = dfs(grid, r + 1, c);
        bool left = dfs(grid, r, c - 1);
        bool right = dfs(grid, r, c + 1);

        // All directions must be safe for a closed island
        return up && down && left && right;
    }

    int closedIsland(vector<vector<int>>& grid) {

        m = grid.size();       // Number of rows
        n = grid[0].size();    // Number of columns

        int count = 0;         // Initially no closed islands

        // Visit every row
        for (int i = 0; i < m; i++) {

            // Visit every column
            for (int j = 0; j < n; j++) {

                // Start DFS only when we find unvisited land
                if (grid[i][j] == 0) {

                    // Count the island only if it is closed
                    if (dfs(grid, i, j)) {
                        count++;
                    }
                }
            }
        }

        return count;  // Final number of closed islands
    }
};
