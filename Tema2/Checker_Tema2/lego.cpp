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
        int nrMax = (K + 1) * (T + 1);
        vector<int> sums(nrMax, INT_MAX);
        vector<vector<int>> coins(nrMax, vector<int>(K + 1, 0));

        sums[0] = 0;

        // problema coin change
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < nrMax; ++k) {
                if (sums[k] != INT_MAX &&
                    k + comb[j] < nrMax &&
                    sums[k] + 1 <= T &&
                    sums[k] + 1 < sums[k + comb[j]]) {
                    sums[k + comb[j]] = sums[k] + 1;
                }
            }
        }

        int index = 1;

        // calculez lungime amaxima a unei secvente consecutive de piese
        while (index < nrMax) {
            int j = index;

            while (j < nrMax && sums[j] != INT_MAX) {
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
    void BKTR(vector<int>& combination, int step) {
        if (step == N) {
            check(combination);
        }

        if (step < N) {
            for (int i = combination[step - 1] + 1; i <= K; ++i) {
                combination[step] = i;
                BKTR(combination, step + 1);
            }
        }
    }

    // rezolvarea problemei
    void solve() {
        vector<int> combination(N + 1);

        combination[0] = 1;
        BKTR(combination, 1);
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
