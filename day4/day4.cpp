#include "../default.hpp"
#include "../aoc_utils.hpp"

class Grid {
public:
    Grid(vector<string>& grid) : m_grid(grid) {
        M = m_grid.size();
        N = m_grid[0].size();
    };

    /* Part 1 */
    int getNumOfAccessibleRolls() {
        int res = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (m_grid[i][j] == skRoll && countNeighbors({i, j}) < 4) {
                    res++;
                }
            }
        }

        return res;
    }

    /* Part 2 */
    int getRemovableRolls() {
        int removed = 0;
        vector<ii> toRemove;
        do {
            toRemove.clear();
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (m_grid[i][j] == skRoll && countNeighbors({i, j}) < 4) {
                        toRemove.push_back({i, j});
                    }
                }
            }

            for (const ii& pos : toRemove) {
                m_grid[pos.first][pos.second] = '.';
            }

            removed += toRemove.size();
        } while (toRemove.size() > 0);

        return removed;
    }

private:
    int countNeighbors(ii pos) {
        int neighbors = 0;
        vector<ii> dirs = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
                           {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        for (const auto& dir : dirs) {
            ii dest = {pos.first + dir.first, pos.second + dir.second};
            if (dest.first >= 0 && dest.first < M && dest.second >= 0 &&
                dest.second < N && m_grid[dest.first][dest.second] == skRoll) {
                neighbors++;
            }
        }

        return neighbors;
    }

    static constexpr char skRoll{'@'};
    vector<string>& m_grid;
    int M{0};
    int N{0};
};

int main() {
    InputReader inputReader;
    inputReader.readInput(4);

    Grid grid(inputReader.getLines());

    cout << grid.getRemovableRolls() << endl;

    return 0;
}
