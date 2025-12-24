#include "../aoc_utils.hpp"
#include "../default.hpp"

int main() {
    InputReader inputReader;
    inputReader.readInput(9);

    vector<Point> redTiles;
    auto rLines = inputReader.getLines();

    for (const string& line : rLines) {
        vector<string> tokens = StringTokenizer::sGetTokens(line, ",");
        /* The coordinates are given as col,row for some reason... */
        redTiles.emplace_back(stoi(tokens[1]), stoi(tokens[0]));
    }

    UINT64 maxArea = 0;
    for (int i = 0; i < redTiles.size(); i++) {
        for (int j = i + 1; j < redTiles.size(); j++) {
            int height = std::abs(redTiles[i].m_row - redTiles[j].m_row) + 1;
            int width = std::abs(redTiles[i].m_col - redTiles[j].m_col) + 1;
            UINT64 area = static_cast<UINT64>(height) * width;

            maxArea = std::max(maxArea, area);
        }
    }

    cout << maxArea << endl;

    return 0;
}
