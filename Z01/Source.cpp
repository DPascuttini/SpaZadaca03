#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

const int REDAKA = 20;
const int STUPACA = 40;

struct Point {
    int redak;
    int stupac;

    Point(int r, int c) : redak(r), stupac(c) {}
};

void plotPath(const vector<Point>& path) {
    vector<vector<char>> grid(REDAKA, vector<char>(STUPACA, '-'));
    
    for (const Point& point : path) {
        grid[point.redak - 1][point.stupac - 1] = 'X';

        system("cls");

        for (int i = 0; i < REDAKA; i++) {
            for (int j = 0; j < STUPACA; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

vector<Point> findPath(const Point& start, const Point& end) {
    vector<Point> path;

    path.push_back(start);

    if (start.stupac < end.stupac) {
        for (int c = start.stupac + 1; c <= end.stupac; c++) {
            path.push_back(Point(start.redak, c));
        }
    } else if (start.stupac > end.stupac) {
        for (int c = start.stupac - 1; c >= end.stupac; c--) {
            path.push_back(Point(start.redak, c));
        }
    }

    if (start.redak < end.redak) {
        for (int r = start.redak + 1; r <= end.redak; r++) {
            path.push_back(Point(r, end.stupac));
        }
    } else if (start.redak > end.redak) {
        for (int r = start.redak - 1; r >= end.redak; r--) {
            path.push_back(Point(r, end.stupac));
        }
    }

    return path;
}

int main() {
    int startR, startS, endR, endS;

    cout << "Redak A(1-20):";
    cin >> startR;
    cout << "Stupac A(1-40): ";
    cin >> startS;

    cout << "Redak B(1-20): ";
    cin >> endR;
    cout << "Stupac B(1-40): ";
    cin >> endS;

    Point start(startR, startS);
    Point end(endR, endS);
    vector<Point> path = findPath(start, end);
    plotPath(path);

    return 0;
}