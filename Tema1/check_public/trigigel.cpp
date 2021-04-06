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

    // procesarea solutiei
    // idee algoritm: pentru fiecare i de la 1 la n aflu
    // cate optiuni valide are
    // se observa ca pt fiecare element nou adaugat
    // solutia este numarul de elemente de la pozitia i
    // + toate subsirurile care se termina cu o anumita valoare astfel:
    // - daca adaugam 0, subsirurile se termina in 2
    // - daca adaugam 1, subsirurile se termina in 0
    // - daca adaugam 2, subsirurile se termina in 1
    // deci retin la fiecare pas cate subsiruri au ultima cifra 0, 1 sau 2
    // la fiecare pas verific ce cifra urmeaza sa fie adaugata si adun
    // la raspuns cate subsiruri nou apar si fac update la acea valoare
    // complexitate temporala => O(n)
    // complexistate temporala => O(1)
    void process() {
        vector<long long> values(3, 0);

        if (n == 1) {
            ans = 1;
            return;
        } else if (n == 2) {
            ans = 3;
            return;
        }

        ans = 6;
        values[0] = 1;
        values[1] = 2;
        values[2] = 3;

        for (long long i = 4; i <= n; ++i) {
            long long valToApp = (i - 1) % 3;
            long long appTo = valToApp == 0 ? 2 : valToApp - 1;

            ans = (ans +  values[appTo] + 1) % mod;
            values[valToApp] = (values[valToApp] + values[appTo] + 1) % mod;
        }
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
