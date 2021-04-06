#include <bits/stdc++.h>
#define mod 1000000007

using namespace std;

ifstream f("trigigel.in");
ofstream g("trigigel.out");

class Solution {
 public:
    long long n;
    long long ans;

    Solution() {
        f >> n;

        ans = 0;
        f.close();
    }

    // functie de inmultit 2 matrice
    void multiplyMatrix(long long A[3][3], long long B[3][3]) {
        long long tmp[3][3];

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                long long sum = 0;

                for (int k = 0; k < 3; ++k) {
                    sum += 1LL * A[i][k] * B[k][j];
                }

                tmp[i][j] = sum % mod;
            }
        }

        memcpy(A, tmp, sizeof(tmp));
    }

    // procesarea solutiei
    // idee algoritm: pentru fiecare i de la 1 la n aflu
    // cate optiuni valide are
    // se observa ca pt fiecare element nou adaugat
    // solutia este numarul de elemente de la pozitia i
    // + toate subsirurile care se termina cu o anumita valoare astfel:
    // - daca adaugam 0, subsirurile se termina in 2
    // - daca adaugam 1, subsirurile se termina in 0
    // - daca adaugam 2, subsirurile se termina in 1
    // dupa ce am generat niste solutii am obtinut o recurenta valida
    // astfel se obtine recurenta dp[i] = 3 + dp[i - 1] + dp[i - 3]
    // Incerc sa folosesc o recurenta de tip Ans = dp * Mat,
    // unde Mat este o matrice patratica pentru a folosi
    // multiplicarea in logn a matricelor
    // Astfel am matricea A = {{0, 0, 1}, {1, 0, 0}, {0, 1, 1}}
    // Cazurile de baza sunt 1 => 1, 2 => 3, 3 => 6
    // formula este ans = dp * A^(n - 3) + [0 0 3] * (A^(n - 3) - I3) * inv
    // unde dp este o matrice patratica 3x3 (deoarece ma ajuta la
    // multiplicare), A este matricea de mai sus, iar ce ramane
    // este obinut din calculul [0 0 3] * (A^(n - 3) - I3) * inv
    // inmultesc cu [0 0 3] pentru ca avem dp[i] = 3 + dp[i - 1] + dp[i - 3]
    // inv este (A - I3)^(-1)
    // astfel calculez prin ridicare la putere in timp logaritmic valoarea
    // lui A^(n - 3) si fac inmultirire. Folosesc doar matrice  3x3 pentru
    // a folosi functia de multiplicare a matricei
    // raspunsul este (dp[0][2] + ans[0][2]) % mod
    // complexitate temporala => O(logn)
    // complexistate spatiala => O(1)

    void process() {
        // cazuri de baza
        if (n == 1) {
            ans = 1;
            return;
        } else if (n == 2) {
            ans = 3;
            return;
        } else if (n == 3) {
            ans = 6;
            return;
        }

        long long A[3][3] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 1}};
        long long inv[3][3] = {{0, 1, 1}, {0, 0, 1}, {1, 1, 1}};
        long long arr[3][3] = {{0, 0, 3}, {0, 0, 0}, {0, 0, 0}};
        long long dp[3][3] = {{1, 3, 6}, {0, 0, 0}, {0, 0, 0}};
        long long multipliedMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

        n -= 3;

        while (n) {
            if (n % 2 == 1) {
                n --;
                multiplyMatrix(multipliedMatrix, A);
            }

            n /= 2;
            multiplyMatrix(A, A);
        }

        // dp * A^(n - 3)
        multiplyMatrix(dp, multipliedMatrix);

        // A^(n - 3) - I3
        multipliedMatrix[0][0] -= 1;
        multipliedMatrix[1][1] -= 1;
        multipliedMatrix[2][2] -= 1;

        // arr * (A^(n - 3) - I3) * inv
        multiplyMatrix(multipliedMatrix, inv);
        multiplyMatrix(arr, multipliedMatrix);

        ans = (dp[0][2] + arr[0][2]) % mod;
    }

    void getResult() {
        g << ans << '\n';
        g.close();
    }
};

int main() {
    Solution sol = Solution();

    sol.process();
    sol.getResult();

    return 0;
}
