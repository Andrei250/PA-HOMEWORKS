#include <bits/stdc++.h>

using namespace std;

ifstream f("stocks.in");
ofstream g("stocks.out");

class Triplet {
 public:
    long long price, minPrice, maxPrice;

    explicit Triplet(long long price, long long minPrice, long long maxPrice) {
        this->price = price;
        this->minPrice = minPrice;
        this->maxPrice = maxPrice;
    }

    long long getLoss() {
        return this->price - this->minPrice;
    }

    long long getProfit() {
        return this->maxPrice - this->price;
    }
};

class Solution {
 public:
    long long N, B, L;
    vector<Triplet> options;
    long long profit;
    long long d[105][505][505];

    Solution() {
        profit = 0;

        f >> N >> B >> L;

        for (long long i = 0; i < N; ++i) {
            long long pr, minPr, maxPr;

            f >> pr >> minPr >> maxPr;

            options.push_back(Triplet(pr, minPr, maxPr));
        }

        f.close();
    }

    void process() {
        for (long long i = 0; i <= N; ++i) {
            for (long long j = 0; j <= B; ++j) {
                for (long long k = 0; k <= L; ++k) {
                    d[i][j][k] = INT_MIN;
                }
            }
        }

        d[0][0][0] = 0;

        for (long long i = 1; i <= N; ++i) {
            long long loss = options[i - 1].getLoss();
            long long price = options[i - 1].price;
            long long minPr = options[i - 1].minPrice;
            long long maxPr = options[i - 1].maxPrice;
            long long prf = options[i - 1].getProfit();

            for (long long b = 0; b <= B; ++b) {
                for (long long l = 0; l <= L; ++l) {
                    d[i][b][l] = max(d[i][b][l], d[i - 1][b][l]);

                    if (b < options[i - 1].price || l < loss ||
                        d[i - 1][b - price][l - loss] == INT_MIN) {
                       continue;
                    }

                    d[i][b][l] = max(d[i][b][l],
                                    d[i - 1][b -price][l - loss] +
                                    prf);
                }
            }
        }

        for (long long b = 0; b <= B; ++b) {
            for (long long l = 0; l <= L; ++l) {
                profit = max(d[N][b][l], profit);
            }
        }
    }

    void getResult() {
        g << profit << '\n';

        g.close();
    }
};

int main(int argc, char ** argv) {
    Solution *solution = new Solution();

    solution->process();
    solution->getResult();

    delete(solution);
    return 0;
}
