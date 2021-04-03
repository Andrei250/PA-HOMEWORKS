#include <bits/stdc++.h>

using namespace std;
ifstream f("ridge.in");
ofstream g("ridge.out");

class Solution {
 public:
    long long N;
    vector<pair<long long, long long> > mountains;
    long long answer;

    Solution() {
        answer = 0;
        f >> N;

        mountains.push_back(make_pair(0, 0));

        for (long long i = 0; i < N; ++i) {
            long long H, C;

            f >> H >> C;
            mountains.push_back(make_pair(H, C));
        }

        f.close();
    }

    void process() {
        vector<vector<long long> > dp(N + 1, vector<long long>(3, LLONG_MAX));

        dp[1][0] = 0;
        dp[1][1] = mountains[1].first - 1 >= 0 ?
                    mountains[1].second : LLONG_MAX;
        dp[1][2] = mountains[1].first - 2 >= 0 ?
                    mountains[1].second * 2 : LLONG_MAX;

        for (long long i = 2; i <= N; ++i) {
            for (long long steps = 0; steps <= 2; ++steps) {
                long long lowest = LLONG_MAX;
                long long value = mountains[i].first - steps;

                if (value < 0) {
                    break;
                }

                if (value != mountains[i - 1].first) {
                    lowest = min(lowest, dp[i - 1][0]);
                }

                if (value != mountains[i - 1].first - 1) {
                    lowest = min(lowest, dp[i - 1][1]);
                }

                if (value != mountains[i - 1].first - 2) {
                    lowest = min(lowest, dp[i - 1][2]);
                }

                if (lowest != LLONG_MAX) {
                    dp[i][steps] = steps * mountains[i].second + lowest;
                }
            }
        }

        answer = min(dp[N][0], min(dp[N][1], dp[N][2]));
    }

    void getResult() {
        g << answer << '\n';
        g.close();
    }
};

int main() {
    Solution sol = Solution();

    sol.process();
    sol.getResult();
    return 0;
}
