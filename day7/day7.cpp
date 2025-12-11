#include "../default.hpp"
#include "../aoc_utils.hpp"

int main() {
    InputReader inputReader;
    inputReader.readInput(7);

    vector<string>& rLines = inputReader.getLines();
    int N = rLines[0].size();

    int startCol = rLines[0].find('S');
    assert(startCol != string::npos);

    /* An unordered map that maps the number of timelines per column. */
    unordered_map<int, long long> timelines = {{startCol, 1}};

    for (const string& line : rLines) {
        unordered_map<int, long long> newTimelines;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != '^' || timelines.find(i) == timelines.end()) {
                continue;
            }

            /* Beam splits here, erase the current column from the timelines and
             * add the left and right ones. */
            long long numOfTimelines = timelines[i];
            assert(numOfTimelines > 0);
            timelines.erase(i);

            // cout << "Split at col: " << i << endl;
            if (i > 0) {
                newTimelines[i - 1] += numOfTimelines;
            }
            if (i < N - 1) {
                newTimelines[i + 1] += numOfTimelines;
            }
        }

        for (const auto& [col, numTimelines] : timelines) {
            newTimelines[col] += numTimelines;
        }
        timelines = newTimelines;
    }

    long long res = 0;
    for (const auto& [col, numTimelines] : timelines) {
        res += numTimelines;
    }

    cout << res << endl;

    return 0;
}
