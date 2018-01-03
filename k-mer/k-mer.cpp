#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    std::srand ((unsigned int)time(NULL));
    clock_t begin;
    begin = clock();

    string temp = "";
    string chro = "";
    int k = 0;

    // 1. 파일 입력 받기
    ifstream openFile("./k-mer.inp");
    if (openFile.is_open()) {
        getline(openFile, temp);
        k = stoi(temp);

        while (getline(openFile, temp)) {
            stringstream ss(temp);
            ss >> temp;
            chro.append(temp);
        }
        openFile.close();
    }

    // 2. 데이터 쪼개기
    int size = chro.length();
    const int division = size - k + 1;

    int radix_index = 6;
    string *datas = new string[division];
    for (int i = 0; i < division; i++) {
        datas[i] = chro.substr(i, k);
    }

    int radix_size = 1;
    for (int i = 0; i < radix_index; i++) {
        radix_size *= 4;
    }
    vector<string> *radix = new vector<string>[radix_size];

    int count = k / radix_index;
    int rest = k % radix_index;
    if (rest != 0) { count++; }
    for (int i = 0; i < count; i++) {
        unsigned long substr_index = k - ((i+1) * radix_index);
        int repeat_count = radix_index;
        if (i == count-1 && rest != 0) {
            repeat_count = rest;
            substr_index = 0;

        }

        for (int j = 0; j < division; j++) {
            int push_index = 0;
            for (int t = 0; t < repeat_count; t++) {
                char chomp = datas[j][substr_index + t];
                int val = 1;
                for (int r = 0; r < radix_index - t - 1; r++) {
                    val *= 4;
                }
                switch (chomp) {
                    case 'a':
                        push_index += 0;
                        break;
                    case 'c':
                        push_index += val;
                        break;
                    case 'g':
                        push_index += 2 * val;
                        break;
                    default:
                        push_index += 3 * val;
                        break;
                }
            }
            radix[push_index].push_back(datas[j]);
        }
        int index = 0;
        for (int j= 0; j < radix_size; j++) {
            for (std::vector<string>::iterator it = radix[j].begin(); it != radix[j].end(); ++it) {
                datas[index] = *it;
                index++;
            }
            radix[j].clear();
        }
    }


    string result = datas[0];
    int same_count = 1;

    string before = datas[0];
    int current_same_count = 1;
    for (int i = 1; i < division; i++) {
        if (before == datas[i]) {
            current_same_count++;
        } else {
            if (same_count < current_same_count) {
                result = before;
                same_count = current_same_count;
            }
            current_same_count = 1;
            before = datas[i];
        }
    }

    if (same_count < current_same_count) {
        result = before;
        same_count = current_same_count;
    }

    // 4. 파일 출력 하기
    ofstream outFile("./k-mer.out");
    outFile << result << endl;
    outFile.close();
    return 0;
}