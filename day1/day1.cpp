#include "../aoc_utils.hpp"
#include "../default.hpp"
#include <cstdlib>

int main() {
    constexpr int N = 100;
    constexpr int startPosition = 50;
    InputReader inputReader;
    inputReader.readInput(1);

    vector<string>& rLines = inputReader.getLines();

    int position = startPosition;
    int zeros = 0;
    for (const auto& line : rLines) {
        char direction = line[0];
        int clicks = std::stoi(line.substr(1));

        if (direction == 'R') {
            zeros += (position + clicks) / N;
            position = (position + clicks) % N;
        } else {
            assert(direction == 'L');
            if (position - clicks < 0) {
                zeros += (std::abs(position - clicks) / N) + (position > 0);
                position = (N - (std::abs(position - clicks) % N)) % N;
            } else {
                position -= clicks;
                zeros += (position == 0);
            }
        }
    }

    cout << zeros << endl;

    return 0;
}
