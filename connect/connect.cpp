#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

class Point {
private:
    double x;
    double y;
    double z;
public:
    Point() {}
    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point(Point &point) {
        this->x = point.get_x();
        this->y = point.get_y();
        this->z = point.get_z();
    }
    void set_xyz(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }
};

Point* ReadPoints(string dir_path, string file_name);
int GetShortestLength(Point* points);
double GetLength(Point point_a, Point point_b);
void PrintFile(string dir_path, string file_name, int result);

int main() {
    Point *points;

    // 1. 파일 입력 받기
    points = ReadPoints("./", "connect.inp");

    // 2. 최단 거리 계산
    int shortest_length = GetShortestLength(points);

    // 3. 파일 출력 하기
    PrintFile("./", "connect.out", shortest_length);

    return 0;
}

Point* ReadPoints(string dir_path, string file_name) {
    ifstream openFile(dir_path + file_name);
    string line;
    int line_count = 0;
    Point *points = 0;

    if (openFile.is_open()) {
        points = new Point[3];
        while (getline(openFile, line)) {
            string buf_1;
            string buf_2;
            string buf_3;
            stringstream ss(line);

            while (ss >> buf_1 && ss >> buf_2 && ss >> buf_3) {
                points[line_count].set_xyz(stod(buf_1), stod(buf_2), stod(buf_3));
            }
            line_count++;
        }
        openFile.close();
    }

    return points;
}

int GetShortestLength(Point* points) {
    double result;
    int a_to_k;
    int b_to_k;
    Point point_a = points[0];
    Point point_b = points[1];
    Point point_k = points[2];
    Point mid_point;

    while(true) {
        a_to_k = (int) GetLength(point_a, point_k);
        b_to_k = (int) GetLength(point_b, point_k);
        mid_point.set_xyz((point_a.get_x() + point_b.get_x()) / 2, (point_a.get_y() + point_b.get_y()) / 2, (point_a.get_z() + point_b.get_z()) / 2);

        if (a_to_k == b_to_k) {
            result = GetLength(mid_point, point_k);
            break;
        } else if (a_to_k < b_to_k) {
            point_b = mid_point;
        } else {
            point_a = mid_point;
        }
    }

    return (int) ceil(result);
}

double GetLength(Point point_a, Point point_b) {
    return sqrt((point_a.get_x() - point_b.get_x()) * (point_a.get_x() - point_b.get_x()) +
                (point_a.get_y() - point_b.get_y()) * (point_a.get_y() - point_b.get_y()) +
                (point_a.get_z() - point_b.get_z()) * (point_a.get_z() - point_b.get_z()));
}

void PrintFile(string dir_path, string file_name, int data) {
    ofstream outFile(dir_path + file_name);
    outFile << data;
    outFile.close();
}