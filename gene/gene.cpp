#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Choice {
private:
    string sequence = "";
    int weight = 0;
public:
    Choice() {}
    Choice(const string &sequence, int weight) : sequence(sequence), weight(weight) {}
    Choice(const Choice &choice) {
        this->sequence = choice.get_sequence();
        this->weight = choice.get_weight();
    }
    void set_sw(const string &sequence, int weight) {
        this->sequence = sequence;
        this->weight = weight;
    }
    const string &get_sequence() const { return sequence; }
    int get_weight() const { return weight; }
};

int main() {
    string chromosome_a;
    string chromosome_b;
    int weights[4];

    // 1. 파일 입력 받기
    ifstream openFile("./gene.inp");
    if (openFile.is_open()) {
        getline(openFile, chromosome_a);
        getline(openFile, chromosome_b);
        string temp;
        getline(openFile, temp);
        stringstream ss(temp);
        for (int i = 0; i < 4; i++) {
            ss >> temp;
            weights[i] = stoi(temp);
        }
        openFile.close();
    }

    int a_length = (int) chromosome_a.length();
    int b_length = (int) chromosome_b.length();
    Choice *choice = new Choice[a_length + 1];

    // 3. SCS 찾기
    for (int i = 1; i < b_length + 1; i++) {
        char b = chromosome_b[i-1];
        Choice *temp_choice = new Choice[a_length + 1];

        for (int j = 1; j < a_length + 1; j++) {
            char a = chromosome_a[j-1];

            if (choice[j].get_weight() > temp_choice[j - 1].get_weight()
                || (choice[j].get_weight() == temp_choice[j - 1].get_weight() && choice[j].get_sequence() < temp_choice[j - 1].get_sequence())) {
                temp_choice[j] = choice[j];
            } else {
                temp_choice[j] = temp_choice[j - 1];
            }

            if (a == b) {
                Choice temp = choice[j-1];
                int weight = 0;
                switch (a) {
                    case 'A': weight = weights[0]; break;
                    case 'G': weight = weights[1]; break;
                    case 'T': weight = weights[2]; break;
                    case 'C': weight = weights[3]; break;
                    default: break;
                }

                string temp_sequence = temp.get_sequence() + a;
                int temp_weight = temp.get_weight() + weight;

                if (temp_weight > temp_choice[j].get_weight()
                    || (temp_weight == temp_choice[j].get_weight() && temp_sequence < temp_choice[j].get_sequence())) {
                    temp_choice[j].set_sw(temp_sequence, temp_weight);
                }
            }
        }

        choice = temp_choice;
    }

    // 4. 파일 출력 하기
    ofstream outFile("./gene.out");
    outFile << choice[a_length].get_sequence() << endl;
    outFile.close();

    return 0;
}