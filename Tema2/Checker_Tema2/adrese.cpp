#include <bits/stdc++.h>

using namespace std;

ifstream f("adrese.in");
ofstream g("adrese.out");

unordered_map<string, int> allEmails;

// clasa pentru a reprezenta un user
class User {
 public:
    string name;
    set<string> finalEmails;
    unordered_set<string> emails;
    int id;

    User() {
    }

    User(int id, string name) {
        this->id = id;
        this->name = name;
    }

    void addEmails(unordered_set<string> emails) {
        for (auto it : emails) {
            this->finalEmails.insert(it);
        }
    }

    void addEmail(string email) {
        this->emails.insert(email);
    }
};

// rezolvarea problemei
// creez un graf cu conexiuni dupa email
// folosesc un unordered_map pt aretine prima aparitie pentru fiecare
// email
// dupa daca exista deja fac legaturile in graf ( bidirectional )
class Adrese {
 public:
    vector<User> users;
    vector<User> finalUsers;
    vector<vector<int>> connections;
    int N;
    int finalN;

    Adrese() {
    }

    static bool cmp(User a, User b) {
        if (a.finalEmails.size() == b.finalEmails.size()) {
            return a.name < b.name;
        }

        return a.finalEmails.size() < b.finalEmails.size();
    }

    // DFS pentru a parcurge graful si a completa toti clientii
    void DFS(int node, vector<bool>& visited, User& client) {
        visited[node] = 1;

        for (auto it : connections[node]) {
            if (!visited[it]) {
                client.name = client.name < users[it].name ?
                                client.name : users[it].name;

                client.addEmails(users[it].emails);
                DFS(it, visited, client);
            }
        }
    }

    // pentru fiecare user nevizitat se paote forma un nou cluster
    // creez userul pentru clusterul respectiv
    void generateAllUsers() {
        vector<bool> visited(N + 1, false);

        for (int i = 1; i <= N; ++i) {
            if (!visited[i]) {
                users[i].addEmails(users[i].emails);
                DFS(i, visited, users[i]);
                finalUsers.push_back(users[i]);
            }
        }
    }

    void readAndSolve() {
        f >> N;

        finalN = N;
        users = vector<User> (N + 1);
        connections = vector<vector<int>> (N + 1);

        for (int i = 1; i <= N; ++i) {
            string name, email;
            int k;

            f >> name >> k;
            // creez userul curent
            users[i] = User(i, name);

            for (int j = 1; j <= k ; ++j) {
                f >> email;

                users[i].emails.insert(email);

                // daca exista deja acest email, atunci userul curent
                // a mai fost inainte si il cuplez la acea entitate
                // creez o conexiune in graf
                if (allEmails.find(email) != allEmails.end()) {
                    if (allEmails[email] != i) {
                        connections[allEmails[email]].push_back(i);
                        connections[i].push_back(allEmails[email]);
                    }

                    continue;
                }

                allEmails[email] = i;
            }
        }

        generateAllUsers();

        // sortezi userii finali dupa nr de emailuri si nume
        sort(finalUsers.begin(), finalUsers.end(), cmp);

        f.close();
    }

    // afisez raspunsul
    void prinResults() {
        g << finalUsers.size() << '\n';

        for (auto it : finalUsers) {
            g << it.name << " " << it.finalEmails.size() << '\n';

            for (auto it2 : it.finalEmails) {
                g << it2 << '\n';
            }
        }

        g.close();
    }
};

int main() {
    Adrese * adrese = new Adrese();

    adrese->readAndSolve();
    adrese->prinResults();
    delete(adrese);
    return 0;
}
