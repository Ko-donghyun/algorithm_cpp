
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Point {
public:
    int i;
    int x;
    int y;
    Point() {};
    Point(int i, int x, int y) {
        this->i = i;
        this->x = x;
        this->y = y;
    };
    void set(int i, int x, int y) {
        this->i = i;
        this->x = x;
        this->y = y;
    };
};

int sarea(Point a, Point b, Point c) {
    return b.x * a.y + c.x * b.y + a.x * c.y - a.x * b.y - b.x * c.y - c.x * a.y;
}

int main() {
    ifstream openFile("./spiral.inp");
    string temp;
    int n = 0;
    Point *points;

    if (openFile.is_open()) {
        getline(openFile, temp);
        n = stoi(temp);
        points = new Point[n+1];

        points[0].set(0, 0, 0);
        n = 1;
        while (getline(openFile, temp)) {
            stringstream ss(temp);
            ss >> temp;
            int x = stoi(temp);
            ss >> temp;
            int y = stoi(temp);

            points[n].set(n, x, y);
            n++;
        }
        openFile.close();
    }

    for (int j = 0; j < n - 1; j++) {
        for (int i = j + 2; i < n; i++) {
            int sarea_v = sarea(points[j], points[j+1], points[i]);
            if (sarea_v > 0) {
                Point temp_p(points[i].i, points[i].x, points[i].y);
                points[i].set(points[j+1].i, points[j+1].x, points[j+1].y);
                points[j+1].set(temp_p.i, temp_p.x, temp_p.y);

            } else if (sarea_v == 0) {
                if ((abs(points[j].x - points[j+1].x) + abs(points[j].y - points[j+1].y)) > (abs(points[j].x - points[i].x) + abs(points[j].y - points[i].y))) {
                    Point temp_p(points[i].i, points[i].x, points[i].y);
                    points[i].set(points[j+1].i, points[j+1].x, points[j+1].y);
                    points[j+1].set(temp_p.i, temp_p.x, temp_p.y);
                }
            }
        }
    }

    ofstream outFile("./spiral.out");
    for (int i = 1; i < n; i++) {
        outFile << points[i].i << " ";
    }
    outFile.close();

    return 0;
}

