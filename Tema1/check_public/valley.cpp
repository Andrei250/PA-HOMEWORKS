#include <bits/stdc++.h>

using namespace std;

ifstream f("valley.in");
ofstream g("valley.out");

class Solution {
 public:
    int N;
    vector<long long> points;
    long long answer;

    // citesc valorile de la tastatura
    Solution() {
        answer = LLONG_MAX;
        f >> N;

        for (int i = 0; i < N; ++i) {
            long long element;

            f >> element;
            points.push_back(element);
        }

        f.close();
    }

    // minimul dintre 2 elemente long long
    long long minimum(long long a, long long b) {
        if (a - b >= 0) {
            return b;
        }

        return a;
    }

    // calculez solutia
    // pentru fiecare element din vector, aflu care este valoarea
    // minima din stanga lui, valoare minima din dreapta lui,
    // costul modificarii tuturor elementelor din stanga (inclusiv el)
    // pentru a obtine o secventa descrescatoare de la stanga la dreapta
    // si costul modificarii tuturor elementelor din dreapta (inclusiv el)
    // pentru a obtine o secventa descrescatoare de la dreapta la stanga
    void process() {
        vector<long long> leftMin(N + 1, 0LL);
        vector<long long> rightMin(N + 1, 0LL);
        vector<long long> removeLeft(N + 1, 0LL);
        vector<long long> removeRight(N + 1, 0LL);

        leftMin[0] = LLONG_MAX;
        removeLeft[0] = 0LL;
        rightMin[N - 1] = LLONG_MAX;
        removeRight[N - 1] = 0LL;

        for (int i = 1; i < N; ++i) {
            leftMin[i] = min(leftMin[i - 1], points[i - 1]);
            removeLeft[i] = removeLeft[i - 1] +
                    (points[i] <= leftMin[i] ? 0 : (points[i] - leftMin[i]));
        }

        for (int i = N - 2; i >= 0; --i) {
            rightMin[i] = min(rightMin[i + 1], points[i + 1]);
            removeRight[i] = removeRight[i + 1] +
                    (points[i] <= rightMin[i] ? 0 : (points[i] - rightMin[i]));
        }

        // calculez solutia, neluand in considerare de 2 ori valoare din i
        // astfel raspunsul este minimul costului fiecarui punct pentru
        // a deveni punctul de minim
        for (int i = 1; i < N - 1; ++i) {
            if (leftMin[i] > rightMin[i]) {
                answer = minimum(answer, removeRight[i] + removeLeft[i - 1]);
            } else {
                answer = minimum(answer, removeLeft[i] + removeRight[i + 1]);
            }
        }
    }

    void getResult() {
        g << answer << '\n';
        g.close();
    }
};


int main() {
    Solution solution = Solution();

    solution.process();
    solution.getResult();

    return 0;
}
