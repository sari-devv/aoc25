
#include "../aoc_utils.hpp"
#include "../default.hpp"

UINT64 getLargestJoltage(const string& line) {
    constexpr int kBatteries = 12;
    int batteriesLeft = kBatteries;
    int start = 0;
    int end = line.size() - batteriesLeft + 1;
    UINT64 res = 0;

    while (batteriesLeft > 0) {
        int maxDigit = 0, maxIdx = -1;
        for (int i = start; i < end; i++) {
            int digit = line[i] - '0';
            if (digit > maxDigit) {
                maxDigit = digit;
                maxIdx = i;
            }
        }

        res = (res * 10) + maxDigit;
        batteriesLeft--;
        start = maxIdx + 1;
        end = line.size() - batteriesLeft + 1;
    }

    return res;
}

int main() {
    InputReader inputReader;
    inputReader.readInput(3);

    auto rLines = inputReader.getLines();
    UINT64 sum = 0;

    for (const string& line : rLines) {
        sum += getLargestJoltage(line);
    }

    cout << sum << endl;

    return 0;
}
