#include <bits/stdc++.h>

using namespace std;
ifstream f("ridge.in");
ofstream g("ridge.out");

class Solution {
 public:
    long long N;
    vector<pair<long long, long long> > mountains;
    long long answer;

    // citire de la tastatura
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

    // cea mai importanta observatie este ca nu este nevoie sa sape
    // mai mult de 2 unitati, deoarece in orice ordine am
    // pune varfurile, trebuie sa fie lua in considerare 3 elemente
    // consecutive pentru a fi diferite
    // astfel pentru fiecare punct calculam solutia cea mai buna
    // excavand din el 0, 1, sau 2 unitati
    // de aceea recurenta este dp[i][step] = minimul dintre
    // valorile celor 3 steps de la i - 1 (astfel incat valoarea
    // mountains[i - 1].first - steps sa fie diferita de
    // valorile considerate pentru minim) si step * mountains[i].second
    // care reprezinta costul excavarii cu step unitati
    // avand in vedere ca ne folosim doar de pasul anterior, o sa
    // folosim o matrice de 3 x 3 ( linia 0 este nefolosita )
    // si dupa calcularea elementelor pentru punctul i in linia 2,
    // acestea se muta pe linia 1
    // la final se ia optiunea ce amai buna dintre cei 3 steps (0, 1, 2)
    // si acela este raspunsul
    // daca la fiecare pas value < 0, atunci optiunea dp[i][step] = LLONG_MAX
    void process() {
        vector<vector<long long> > dp(3, vector<long long>(3, LLONG_MAX));

        dp[1][0] = 0;
        dp[1][1] = mountains[1].first - 1 >= 0 ?
                    mountains[1].second : LLONG_MAX;
        dp[1][2] = mountains[1].first - 2 >= 0 ?
                    mountains[1].second * 2 : LLONG_MAX;

        for (long long i = 2; i <= N; ++i) {
            for (long long steps = 0; steps <= 2; steps++) {
                long long lowest = LLONG_MAX;
                long long value = mountains[i].first - steps;

                if (value < 0) {
                    dp[2][steps] = LLONG_MAX;
                    continue;
                }

                if (value != mountains[i - 1].first) {
                    lowest = min(lowest, dp[1][0]);
                }

                if (value != mountains[i - 1].first - 1) {
                    lowest = min(lowest, dp[1][1]);
                }

                if (value != mountains[i - 1].first - 2) {
                    lowest = min(lowest, dp[1][2]);
                }

                if (lowest != LLONG_MAX) {
                    dp[2][steps] = steps * mountains[i].second + lowest;
                }
            }

            dp[1][0] = dp[2][0];
            dp[1][1] = dp[2][1];
            dp[1][2] = dp[2][2];
        }

        answer = min(dp[1][0], min(dp[1][1], dp[1][2]));
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
