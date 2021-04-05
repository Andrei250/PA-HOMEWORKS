#include <bits/stdc++.h>
#define mod 1000000007

using namespace std;

ifstream f("trigigel.in");
ofstream g("trigigel.out");

class Solution {
 public:
    int n;
    long long ans;

    Solution() {
        f >> n;

        ans = n;
        f.close();
    }

    void process() {
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
