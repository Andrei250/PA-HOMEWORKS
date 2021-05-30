#include <bits/stdc++.h>

using namespace std;

ifstream f("adrese.in");
ofstream g("adrese.out");

unordered_map<string, int> allEmails;

// clasa pentru a reprezenta un user
class User {
 public:
    string name;
    set<string> emails;
    int id;

    User(int id, string name) {
        this->id = id;
        this->name = name;
    }

    void addEmails(set<string> emails) {
        for (auto it : emails) {
            this->emails.insert(it);
        }
    }

    void addEmail(string email) {
        this->emails.insert(email);
    }
};

// rezolvarea problemei
// am nevoie de 2 vectori de pointeri la User
// unul pentru a avea userii finali ( unici ) si altul pentru
// a retine pentru fiecare user initial ce entitate ii apartine
// Ideea este ca pentru fiecare client verific daca
// adresa respectiv ade email a mai existat
// pentru fiecare email retin primul ID intalnit intr-un hashmap( O(1) )
class Adrese {
 public:
    vector<User*> users;
    vector<User*> finalUsers;
    int N;
    int finalN;

    Adrese() {
    }

    static bool cmp(User* a, User* b) {
        if (a->emails.size() == b->emails.size()) {
            return a->name < b->name;
        }

        return a->emails.size() < b->emails.size();
    }

    void readAndSolve() {
        f >> N;

        finalN = N;
        users = vector<User*> (N + 1);

        for (int i = 1; i <= N; ++i) {
            string name, email;
            int k, parentId = i;
            set<string> emails;

            f >> name >> k;

            for (int j = 1; j <= k ; ++j) {
                f >> email;

                emails.insert(email);

                // daca exista deja acest email, atunci userul curent
                // a mai fost inainte si il cuplez la acea entitate
                if (allEmails.find(email) != allEmails.end()) {
                    if (allEmails[email] != i) {
                        parentId = allEmails[email];
                    }

                    continue;
                }

                allEmails[email] = i;
            }

            // daca a mai existat acest user, atunci in vectorul
            // cu toti userii pun pointerul catre userul deja existent
            if (parentId != i) {
                finalN--;
                users[i] = users[parentId];
                users[i]->addEmails(emails);

                if (name < users[i]->name) {
                    users[i]->name = name;
                }

                continue;
            }

            // daca nu creez un nou user
            User *currentUser = new User(i, name);
            currentUser->emails = emails;
            users[i] = currentUser;
            finalUsers.push_back(currentUser);
        }

        // sortezi userii finali dupa nr de emailuri si nume
        sort(finalUsers.begin(), finalUsers.end(), cmp);

        f.close();
    }

    // afisez raspunsul
    void prinResults() {
        g << finalN << '\n';

        for (auto it : finalUsers) {
            g << it->name << " " << it->emails.size() << '\n';

            for (auto it2 : it->emails) {
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
