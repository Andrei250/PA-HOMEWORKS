#include <bits/stdc++.h>

using namespace std;

ifstream f("poduri.in");
ofstream g("poduri.out");

class Poduri {
 public:
    int start, stop;
    int N, M;
    int minimum;
    vector<vector<int>> mp;
    unordered_map<int, vector<vector<int>>> directions;

    // constructor fara parametrii pentru initializarea directiilor
    // -1 => nu se poate merge
    // -2 => podul D
    // -3 => podul O
    // -4 => podul V
    Poduri() {
        start = stop = N = M;
        minimum = INT_MAX;

        directions[-2].push_back({-1, 1, 0, 0});
        directions[-2].push_back({0, 0, -1, 1});

        directions[-3].push_back({0, 0});
        directions[-3].push_back({-1, 1});

        directions[-4].push_back({-1, 1});
        directions[-4].push_back({0, 0});
    }

    void readInput() {
        f >> N >> M >> start >> stop;

        mp = vector<vector<int>> (N + 1, vector<int> (M + 1));
        char x;

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                f >> x;

                if (x == '.') {
                    mp[i][j] = -1;
                } else if (x == 'D') {
                    mp[i][j] = -2;
                } else if (x == 'O') {
                    mp[i][j] = -3;
                } else {
                    mp[i][j] = -4;
                }
            }
        }

        f.close();
    }

    // functie care verifica daca o pozitie e afara
    bool isOutside(int x, int y) {
        if (x < 1 || y < 1 || x > N || y > M) {
            return true;
        }

        return false;
    }

    void solve() {
        // coada pentru a retine distanta si pozitia pe harta
        // BFS pe matrice
        queue<pair<int, pair<int, int>>> Q;

        Q.push(make_pair(0, make_pair(start, stop)));

        // cat timp am noduri incerc sa merg mai departe pe harta
        // astfel iau pentru fiecare pozitie directiile in care poate merge
        // si pun pe pozitia pozX pozY valoarea distantei
        // stiu ca daca s-a ajuns intr-un punct atunci nu mai exista o
        // solutie mai optima ca distanta.
        // deci merg doar pe portiunile unde valoarea este < decat -1
        // -1 => apa si valorile >= 0 sunt distante parcurse
        while (!Q.empty()) {
            int distance = Q.front().first;
            int pozX = Q.front().second.first;
            int pozY = Q.front().second.second;

            Q.pop();

            // daca deja s-a vizitat casuta, trec la urmatoarea
            if (mp[pozX][pozY] >= -1) {
                continue;
            }

            vector<vector<int>> currDir = directions[mp[pozX][pozY]];

            mp[pozX][pozY] = distance;

            // merg in directiile posibile in functie de pod
            for (int k = 0; k < currDir[0].size(); ++k) {
                int newX = pozX + currDir[0][k];
                int newY = pozY + currDir[1][k];

                if (isOutside(newX, newY)) {
                    minimum = min(minimum, distance + 1);
                    continue;
                }

                // daca pot merge pe acea pozitie o bag in coada
                if (mp[newX][newY] < -1) {
                    Q.push(make_pair(distance + 1, make_pair(newX, newY)));
                }
            }
        }

        // daca nu avem un minim diferit, atunci nu s-a iesit pe uscat
        minimum = minimum == INT_MAX ? -1 : minimum;
    }

    void printAnswer() {
        g << minimum << '\n';
        g.close();
    }
};

int main() {
    Poduri *prob = new Poduri();

    prob->readInput();
    prob->solve();
    prob->printAnswer();

    return 0;
}
