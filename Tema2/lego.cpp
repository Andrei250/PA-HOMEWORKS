#include <bits/stdc++.h>

using namespace std;

ifstream f("lego.in");
ofstream g("lego.out");

class Lego {
 public:
    int N, K, T;
    vector<int> pieces;
    int maximum;

    Lego() {
        maximum = 0;
    }

    // creez un vector cu toate sumele ce se pot forma cu aceasta
    // combinatie de numere
    // astfel sums[k] = numarul minim de lego pt a obtine suma k
    // matricea coins este pentru a tine numarul de lego pentru
    // fiecare piesa
    void check(vector<int>& comb) {
        vector<int> sums(3000, INT_MAX);
        vector<vector<int>> coins(3000, vector<int>(K + 1, 0));

        sums[0] = 0;

        // problema coin change
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < 3000; ++k) {
                if (sums[k] != INT_MAX &&
                    k + comb[j] < 3000 && 
                    sums[k] + 1 <= T && 
                    sums[k] + 1 < sums[k + comb[j]] &&
                    coins[k][comb[j]] + 1 <= N) {
                    sums[k + comb[j]] = sums[k] + 1;
                    coins[k + comb[j]][comb[j]] = coins[k][comb[j]] + 1;
                }
            }
        }

        int index = 1;

        // calculez lungime amaxima a unei secvente consecutive de piese
        while (index < 3000) {
            int j = index;

            while (j < 3000 && sums[j] != INT_MAX) {
                j++;
            }

            // daca e > maximum atunci este o noua solutie
            if (j - index > maximum) {
                maximum = j - index;
                pieces = comb;
            }

            index = j + 1;
        }
    }

    // Backtracking pt a genera toate solutiile
    void BKTR(vector<int>& combination, vector<bool>& visited, int step) {
        if (step == N) {
            check(combination);
        }

        if (step < N) {
            for (int i = combination[step - 1]; i <= K; ++i) {
                if (!visited[i]) {
                    visited[i] = true;
                    combination[step] = i;
                    BKTR(combination, visited, step + 1);
                    visited[i] = false;
                }
            }
        }
    }

    // rezolvarea problemei
    void solve() {
        vector<bool> visited(K + 1, false);
        vector<int> combination(N + 1);

        visited[1] = true;
        combination[0] = 1;

        BKTR(combination, visited, 1);
    }

    void readInput() {
        f >> K >> N >> T;
        f.close();
    }

    void printOutput() {
        g << maximum << '\n';

        for (int i = 0; i < N; ++i) {
            g << pieces[i] << " ";
        }

        g << '\n';
        g.close();
    }
};

int main() {
    Lego * lego = new Lego();

    lego->readInput();
    lego->solve();
    lego->printOutput();
    delete(lego);
    return 0;
}