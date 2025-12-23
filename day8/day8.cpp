#include "../default.hpp"
#include "../aoc_utils.hpp"
#include <numeric>

class UnionFind {
public:
    UnionFind(int n) : m_parents(n), m_sizes(n, 1), m_numGroups(n) {
        std::iota(m_parents.begin(), m_parents.end(), 0);
    }

    int find(int x) {
        assert(x < m_parents.size());
        if (m_parents[x] != x) {
            m_parents[x] = find(m_parents[x]);
        }

        return m_parents[x];
    }

    void unite(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent) {
            return;
        }

        m_numGroups--;
        int x_size = m_sizes[x_parent];
        int y_size = m_sizes[y_parent];

        if (x_size < y_size) {
            m_parents[x_parent] = y_parent;
            m_sizes[y_parent] += x_size;
        } else {
            m_parents[y_parent] = x_parent;
            m_sizes[x_parent] += y_size;
        }
    }

    const vector<int> getSizes() {
        /* Not all the entries in the m_sizes array are correct.
         * The entries that represent actual sizes are the ones
         * that belong to the parent of each group only. */
        vector<int> actualSizes;
        for (int i = 0; i < m_parents.size(); i++) {
            if (m_parents[i] == i) {
                actualSizes.push_back(m_sizes[i]);
            }
        }

        return actualSizes;
    }

    const int getNumGroups() {
        return m_numGroups;
    }

private:
    vector<int> m_parents;
    vector<int> m_sizes;
    int m_numGroups{-1};
};

struct Position {
    Position(int x1, int y1, int z1) : x(x1), y(y1), z(z1) {};
    int x{0};
    int y{0};
    int z{0};

    static double sCalcDist(const Position& p1, const Position& p2) {
        UINT64 x_diff = p1.x - p2.x;
        UINT64 y_diff = p1.y - p2.y;
        UINT64 z_diff = p1.z - p2.z;

        return std::sqrt((x_diff * x_diff) + (y_diff * y_diff) +
                         (z_diff * z_diff));
    }
};

class Engineer {
public:
    Engineer(const vector<string>& rLines) : m_circuits(rLines.size()) {
        for (const string& line : rLines) {
            auto tokens = StringTokenizer::sGetTokens(line, ",");

            m_positions.emplace_back(std::stoi(tokens[0]), std::stoi(tokens[1]),
                                     std::stoi(tokens[2]));
        }

        makeDistAndPairHeap();
    }

    int connectPairs() {
        /* Connect the first k pairs */
        for (int i = 0; i < skNumOfPairsToCalc; i++) {
            const DistAndPair& top = m_heap.top();
            m_circuits.unite(top.m_p1, top.m_p2);
            m_heap.pop();
        }

        /* Return the product of the largest 3 circuits. */
        auto sizes = m_circuits.getSizes();

        priority_queue<int, vector<int>> sizeHeap(sizes.begin(), sizes.end());

        int product = 1;
        for (int i = 0; i < 3; i++) {
            // cout << "Biggest size: " << sizeHeap.top() << endl;
            product *= sizeHeap.top();
            sizeHeap.pop();
        }

        return product;
    }

    UINT64 connectPairsPart2() {
        UINT64 x_product = 0;
        while (m_heap.empty() == false && m_circuits.getNumGroups() > 1) {
            const DistAndPair& top = m_heap.top();
            x_product = m_positions[top.m_p1].x * m_positions[top.m_p2].x;
            // cout << "Uniting " << top.m_p1 << " and " << top.m_p2 << endl;
            m_circuits.unite(top.m_p1, top.m_p2);
            m_heap.pop();
        }

        return x_product;
    }

private:
    struct DistAndPair {
        DistAndPair(double dist, int p1, int p2)
            : m_dist(dist),
              m_p1(p1),
              m_p2(p2) {};

        struct Compare {
            bool operator()(const DistAndPair& p1, const DistAndPair& p2) {
                return p1.m_dist > p2.m_dist;
            }
        };

        double m_dist;
        int m_p1;
        int m_p2;
    };

    void makeDistAndPairHeap() {
        for (int i = 0; i < m_positions.size(); i++) {
            for (int j = i + 1; j < m_positions.size(); j++) {
                double dist =
                    Position::sCalcDist(m_positions[i], m_positions[j]);
                m_heap.push(DistAndPair(dist, i, j));
            }
        }
    }

    static constexpr int skNumOfPairsToCalc{1000};

    vector<Position> m_positions;
    priority_queue<DistAndPair, vector<DistAndPair>, DistAndPair::Compare>
        m_heap;

    UnionFind m_circuits;
};

int main() {
    InputReader inputReader;
    inputReader.readInput(8);

    Engineer engineer(inputReader.getLines());

    cout << engineer.connectPairsPart2() << endl;

    return 0;
}
