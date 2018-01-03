#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <set>

using namespace std;

class Point {
public:
    int id; int w; int x; int y;
    Point() {}
    int distance(const Point& target) { return abs(x - target.x) + abs(y - target.y); }
    friend bool operator< (const Point& lhs, const Point& rhs) {
        return lhs.id < rhs.id;
    }
};

int main() {
    Point *points = 0;
    string temp = "";
    int n = 0;
    int total_w = 1;

    // 1. 파일 입력 받기
    ifstream openFile("./drone.inp");
    if (openFile.is_open()) {
        getline(openFile, temp); n = stoi(temp);
        points = new Point[n];

        n = 0;
        while (getline(openFile, temp)) {
            stringstream ss(temp);
            ss >> temp; points[n].id = stoi(temp);
            ss >> temp; points[n].w = stoi(temp);
            total_w += stoi(temp);
            ss >> temp; points[n].x = stoi(temp);
            ss >> temp; points[n].y = stoi(temp);
            n++;
        }
        openFile.close();
    }

    // 2. 정렬
    for (int i = 1; i < n; i++) {
        Point value = points[i];
        int j = i - 1;

        while(j >= 0 && value < points[j]) {
            points[j + 1] = points[j];
            j--;
        }
        points[j + 1] = value;
    }

    // 3. 최소값 찾기
    int smallest = 9999999;
    stack<int> stack1;
    set<int> set1;
    set<int>::iterator iterator1;

    for (int i = 1; i < n; i++) {
        stack1.push(i);
    }

    int *order = new int[n];
    order[0] = 0;

    bool is_done = false;
    while (!is_done) {
        int stop = -1;
        int temp_w = total_w;
        stack<int> stack2(stack1);
        int index;
        for (index = 1; index < n; index++) {
            order[index] = stack2.top();
            stack2.pop();
        }

        int weight = 1;
        int p = temp_w * points[order[index-1]].distance(points[0]);
        for (int i = index-1; i > 0; i--) {
            temp_w -= points[order[i]].w;
            p += temp_w * points[order[i]].distance(points[order[i-1]]);
            if (smallest < p) {
                stop = i-1;
                break;
            }
        }

        if (stop > 2) {
            int max = -1;
            int top = 0;

            for (int i = 0; i < stop; i++) {
                top = stack1.top();
                set1.insert(top);
                stack1.pop();
                if (max < top) {
                    max = top;
                }
            }

            int before_top = top;
            if (top == max) {
                for (int i = stop; i < n; i++) {
                    if (stack1.size() == 0) {
                        is_done = true;
                        break;
                    }
                    top = stack1.top();
                    set1.insert(top);
                    stack1.pop();

                    if (before_top > top) {
                        break;
                    }
                    before_top = top;
                }
            }

            if (is_done) {
                break;
            }

            iterator1 = set1.find(top);
            iterator1++;
            stack1.push(*iterator1);
            set1.erase(iterator1);

            for (set<int>::iterator iter = set1.begin(); iter != set1.end(); iter++) {
                stack1.push(*iter);
            }
            set1.clear();
            continue;
        }

        if (smallest > p) {
            smallest = p;

            cout << p << " : 1";
            for (int i = n-1; i >= 0; i--) {
                cout << " " << order[i] + 1;
            }
            cout << endl;
        }

        int before_value = stack1.top();
        set1.insert(before_value);
        stack1.pop();
        for (int a = 0; a < n-2; a++) {
            int value = stack1.top();
            set1.insert(value);
            stack1.pop();

            if (value < before_value) {
                iterator1 = set1.find(value);
                iterator1++;
                stack1.push(*iterator1);
                set1.erase(iterator1);

                for (set<int>::iterator iter = set1.begin(); iter != set1.end(); iter++) {
                    stack1.push(*iter);
                }
                set1.clear();
                break;
            }
            before_value = value;

            if (set1.size() == n-1) {
                is_done = true;
                break;
            }
        }
    }

    // 4. 파일 출력 하기
    ofstream outFile("./drone.out");
    outFile << smallest << endl;
    outFile.close();

    return 0;
}