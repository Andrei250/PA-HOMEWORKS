#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    int answer;
    vector<pair<int, int>> computers;
    int numberOfComputers;
    int totalPrice;

    // contructor explicit pentru a deschide fisierul de input dat ca
    // parametru
    // citesc valorile de la tastatura
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

    // verific daca valoarea curenta poate fi o valoare valida
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

    // fac o cautare binara intre lower si upper pentru a gasii valoarea
    // valida
    // astfel daca mid este o valoarea valida, caut in dreapta (pentru
    // a imbunatati solutia) sau in stanga in caz contrar
    void process() {
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
    }

    // afisez raspunsul
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

    delete(solution);

    return 0;
}
