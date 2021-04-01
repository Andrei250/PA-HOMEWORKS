#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    int answer;
    vector<pair<int, int>> computers;
    int numberOfComputers;
    int totalPrice;

    explicit Solution(string input) {
        answer = 0;
        ifstream f(input);

        f >> numberOfComputers >> totalPrice;

        for (int i = 0; i < numberOfComputers; ++i) {
            int processors, units;

            f >> processors >> units;
            computers.push_back(make_pair(processors, units));
        }

        f.close();
    }

    static bool cmp(pair<int, int> a, pair<int, int> b) {
        if (a.first == b.first) {
            return a.second > b.second;
        }

        return a.first < b.first;
    }

    bool processValue(int value) {
        int computedPrice = 0;

        for (auto it : computers) {
            if (it.first < value) {
                if (1LL * (value - it.first) * it.second + 1LL * computedPrice >
                    1LL * totalPrice) {
                    return false;
                }

                computedPrice += (value - it.first) * it.second;
            }
        }

        answer = max(answer, value);
        return true;
    }

    void process() {
        // int computedPrice = 0;
        bool done = false;

        int lower = 0, upper = INT_MAX - 1;

        while (lower <= upper) {
            int mid = (upper - lower) / 2 + lower;

            if (processValue(mid)) {
                lower = mid + 1;
            } else {
                upper = mid - 1;
            }
        }

        // sort(computers.begin(), computers.end(), cmp);
        // while (!done && computedPrice < totalPrice) {
        //     for (int index = 0; index < computers.size(); index++) {
        //         if (computedPrice + computers[index].second > totalPrice) {
        //             done = true;
        //             break;
        //         }
        //         computedPrice += computers[index].second;
        //         computers[index].first++;
        //         if (index < computers.size() - 1 &&
        //               computers[index].first - 1 !=
        //               computers[index + 1].first ) {
        //             break;
        //         }
        //     }
        // }
        // answer = INT_MAX;
        // for (auto it : computers) {
        //     answer = min(answer, it.first);
        // }
    }

    void getResult(string output) {
        ofstream g(output);

        g << answer << '\n';

        g.close();
    }
};

int main(int argc, char **argv) {
    string input, output;

    if (argc < 2) {
        input = "crypto.in";
        output = "crypto.out";
    } else {
        input = string(argv[1]);
        output = string(argv[2]);
    }

    Solution *solution = new Solution(input);

    solution->process();
    solution->getResult(output);

    return 0;
}
