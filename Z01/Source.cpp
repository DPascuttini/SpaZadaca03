#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

const int REDAKA = 20;
const int STUPACA = 40;

void iscrtajPut(int startRedak, int startStupac, int ciljRedak, int ciljStupac) {
    if (startRedak < 1 || startRedak > REDAKA || startStupac < 1 || startStupac > STUPACA ||
        ciljRedak < 1 || ciljRedak > REDAKA || ciljStupac < 1 || ciljStupac > STUPACA) {
        cout << "Neispravni ulazni parametri!\n";
        return;
    }
    vector<vector<char>> polje(REDAKA, vector<char>(STUPACA, '-'));

    polje[startRedak - 1][startStupac - 1] = 'A';
    polje[ciljRedak - 1][ciljStupac - 1] = 'B';
    int pomakRedak = (ciljRedak > startRedak) ? 1 : -1;
    int pomakStupac = (ciljStupac > startStupac) ? 1 : -1;
    int trenutniRedak = startRedak;
    int trenutniStupac = startStupac;

    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            cout << polje[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    while (trenutniRedak != ciljRedak || trenutniStupac != ciljStupac) {
      
        this_thread::sleep_for(chrono::milliseconds(100));
        system("cls");
        polje[trenutniRedak - 1][trenutniStupac - 1] = 'X';
        for (int i = 0; i < REDAKA; i++) {
            for (int j = 0; j < STUPACA; j++) {
                cout << polje[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        polje[trenutniRedak - 1][trenutniStupac - 1] = '-';

        trenutniRedak += pomakRedak;
        trenutniStupac += pomakStupac;
    }
}

int main() {
    int startRedak, startStupac, ciljRedak, ciljStupac;
    cout << "A redak: ";
    cin >> startRedak;
    cout << "A stupac: ";
    cin >> startStupac;
    cout << "B redak: ";
    cin >> ciljRedak;
    cout << "B stupac: ";
    cin >> ciljStupac;

    iscrtajPut(startRedak, startStupac, ciljRedak, ciljStupac);

    return 0;
}