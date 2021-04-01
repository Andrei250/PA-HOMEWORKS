#include <bits/stdc++.h>

using namespace std;

class Solution {

};

int main() {
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

    return 0;
}