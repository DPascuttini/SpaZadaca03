#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <chrono>
#include <thread>

using namespace std;

const int REDAKA = 20;
const int STUPACA = 40;
const int INF = numeric_limits<int>::max();

struct Point {
    int redak;
    int stupac;

    Point(int r, int c) : redak(r), stupac(c) {}
};

struct Cell {
    int redak;
    int stupac;
    int udaljenost;
    Cell* prethodnik;

    Cell(int r, int s, int d, Cell* p) : redak(r), stupac(s), udaljenost(d), prethodnik(p) {}
};

void plotPath(const vector<Cell*>& path, vector<vector<char>>& polje) {
    system("cls");

    for (int i = 0; i < REDAKA; i++) {
        for (int j = 0; j < STUPACA; j++) {
            cout << polje[i][j] << " ";
        }
        cout << endl;
    }

    for (const Cell* cell : path) {
        this_thread::sleep_for(chrono::milliseconds(100));
        system("cls");
        polje[cell->redak - 1][cell->stupac - 1] = 'X';
        for (int i = 0; i < REDAKA; i++) {
            for (int j = 0; j < STUPACA; j++) {
                cout << polje[i][j] << " ";
            }
            cout << endl;
        }
        polje[cell->redak - 1][cell->stupac - 1] = '-';
    }
}

vector<Cell*> findPath(const Point& start, const Point& end, vector<vector<char>>& polje) {
    vector<vector<int>> udaljenosti(REDAKA, vector<int>(STUPACA, INF));
    udaljenosti[start.redak - 1][start.stupac - 1] = 0;

    vector<Cell*> path;

    priority_queue<pair<int, Cell*>, vector<pair<int, Cell*>>, greater<pair<int, Cell*>>> pq;
    pq.push({ 0, new Cell(start.redak, start.stupac, 0, nullptr) });

    while (!pq.empty()) {
        Cell* trenutnaCelija = pq.top().second;
        pq.pop();

        int trenutniRedak = trenutnaCelija->redak;
        int trenutniStupac = trenutnaCelija->stupac;
        int trenutnaUdaljenost = trenutnaCelija->udaljenost;

        if (trenutniRedak == end.redak && trenutniStupac == end.stupac) {
            while (trenutnaCelija != nullptr) {
                path.push_back(trenutnaCelija);
                trenutnaCelija = trenutnaCelija->prethodnik;
            }
            break;
        }

        int susjedneRedak[4] = { trenutniRedak - 1, trenutniRedak + 1, trenutniRedak, trenutniRedak };
        int susjedneStupac[4] = { trenutniStupac, trenutniStupac, trenutniStupac - 1, trenutniStupac + 1 };

        for (int i = 0; i < 4; i++) {
            int susjedniRedak = susjedneRedak[i];
            int susjedniStupac = susjedneStupac[i];

            if (susjedniRedak >= 1 && susjedniRedak <= REDAKA && susjedniStupac >= 1 && susjedniStupac <= STUPACA) {
                if (polje[susjedniRedak - 1][susjedniStupac - 1] != '#') {
                    int novaUdaljenost = trenutnaUdaljenost + 1;
                    if (novaUdaljenost < udaljenosti[susjedniRedak - 1][susjedniStupac - 1]) {
                        udaljenosti[susjedniRedak - 1][susjedniStupac - 1] = novaUdaljenost;
                        pq.push({ novaUdaljenost, new Cell(susjedniRedak, susjedniStupac, novaUdaljenost, trenutnaCelija) });
                    }
                }
            }
        }
    }

    reverse(path.begin(), path.end());

    return path;
}

int main() {
    int startR, startS, endR, endS;

    cout << "Redak A (1-20): ";
    cin >> startR;
    cout << "Stupac A (1-40): ";
    cin >> startS;

    cout << "Redak B (1-20): ";
    cin >> endR;
    cout << "Stupac B (1-40): ";
    cin >> endS;

    Point start(startR, startS);
    Point end(endR, endS);

    vector<vector<char>> polje(REDAKA, vector<char>(STUPACA, '-'));

    // Zid
    polje[0][20] = '#';
    polje[1][20] = '#';
    polje[2][20] = '#';
    polje[3][20] = '#';
    polje[4][20] = '#';
    polje[5][20] = '#';
    polje[6][20] = '#';
    polje[7][20] = '#';
    polje[8][20] = '#';
    polje[9][20] = '#';
    polje[10][20] = '#';
    polje[12][20] = '#';
    polje[13][20] = '#';
    polje[14][20] = '#';
    polje[15][20] = '#';
    polje[16][20] = '#';
    polje[17][20] = '#';
    polje[18][20] = '#';
    polje[19][20] = '#';

    vector<Cell*> path = findPath(start, end, polje);
    plotPath(path, polje);

    for (Cell* cell : path) {
        delete cell;
    }

    return 0;
}