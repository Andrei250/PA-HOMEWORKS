#include <bits/stdc++.h>

using namespace std;

ifstream f("retea.in");
ofstream g("retea.out");

class Retea {
 public:
    int N, M;
    vector<vector<int>> edges;
    vector<vector<int>> articulationPoints;
    vector<int> low, dfn;
    int dfsChecked = 0;

    Retea() {
    }

    // citesc inputul si formez graful
    void readInput() {
        f >> N >> M;

        edges = vector<vector<int>> (N + 1);
        articulationPoints = vector<vector<int>> (N + 1, vector<int>(1, 0));
        low = vector<int> (N + 1);
        dfn = vector<int> (N + 1, -1);

        for (int i = 0; i < M; ++i) {
            int x , y;

            f >> x >> y;

            edges[x].push_back(y);
            edges[y].push_back(x);
        }

        f.close();
    }

    // DFS pentru a gasii nodurile de articulatie
    // practic in low retin cel mai de sus stramosi la care se poate
    // ajunge pe o alta cale fata de cea din parcurgerea DFS
    // apoi daca intr-un nod low[it] >= dfn[node] inseamna ca node
    // este punct de articulatie si adaug numarul de noduri din componenta
    // biconexa care se formeaza pe acea cale
    // retin in articulationPoints[node][0] numarul de noduri care se
    // afla sub riscul de deconectare fata de graful principal prin stergerea
    // nodului node
    int DFS(int node) {
        int copii = 0, copiiDfs = 0;

        dfn[node] = low[node] = ++dfsChecked;

        for (auto it : edges[node]) {
            if (dfn[it] == -1) {
                copiiDfs = DFS(it);
                copii += copiiDfs;
                low[node] = min(low[node], low[it]);

                if (low[it] >= dfn[node]) {  // nod de articulatie
                    articulationPoints[node][0] += copiiDfs;
                    articulationPoints[node].push_back(copiiDfs);
                }
            } else {
                low[node] = min(low[node], dfn[it]);
            }
        }

        return copii + 1;
    }

    // pentru fiecare nod, verific daca e nod de articulatie
    // daca nu este nod de articulatie, atunci raspunsul este
    // 2 * (N - 1) => fiecare nod nu se mai conecteaza cu nodul sters
    // si nodul sters nu se conecteaza cu celalalte noduri
    // daca este nod de articulatie , atunci suma finala este
    // 2 * (N - 1) (aceeasi logica ca la conditia de nu a fi)
    // + fiecare combinatie de componente conexe
    // Adica daca nodul curent sparge graful in mai multe componente
    // de lungimi x1, x2, .. xn, atunci de fiecare data adun
    // x1 * (N - 1 - x1)
    // la final aduc si situatia cu componenta conexa aflata deasupra
    // nodului sters in arborele DFS (deoarece tin cont doar de numarul)
    // de noduri aflate mai jos
    void solveAndPrint() {
        DFS(1);

        for (int i = 1; i <= N; ++i) {
            if (articulationPoints[i][0] == 0) {
                g << 2 * (N - 1) << '\n';
            } else {
                int number = 2 * (N - 1);

                for (int j = 1; j < articulationPoints[i].size(); ++j) {
                    number += articulationPoints[i][j] *
                                ((N - 1) - articulationPoints[i][j]);
                }

                number += ((N - 1) - articulationPoints[i][0]) *
                            articulationPoints[i][0];

                g << number << '\n';
            }
        }

        g.close();
    }
};

int main() {
    Retea * retea = new Retea();

    retea->readInput();
    retea->solveAndPrint();
    delete(retea);
    return 0;
}
