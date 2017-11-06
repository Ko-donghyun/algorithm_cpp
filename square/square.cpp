#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

class Numbers {
private:
    int number_count;
    int *numbers;
public:
    Numbers() {}
    Numbers(int *numbers, int number_count) {
        this->numbers = numbers;
        this->number_count = number_count;
    }
    void set_numbers(int *numbers) {
        this->numbers = numbers;
    }
    int* get_numbers() {
        return this->numbers;
    }

    void set_number_count(int number_count) {
        this->number_count = number_count;
    }

    int get_number_count() {
        return this->number_count;
    }
};

class Node {
private:
    int value;
    Node *next_node;
public:
    Node() {
        this->next_node = 0;
    };
    Node(int value) {
        this->value = value;
        this->next_node = 0;
    };
    int get_value() {
        return this->value;
    }
    Node* get_next_node() {
        return this->next_node;
    }
    void set_next_node(Node *next_node) {
        this->next_node = next_node;
    }
};

class LinkedList {
private:
    Node *head;
public:
    LinkedList() {
        this->head = 0;
    };
    LinkedList(Node *next_node) {
        this->head = 0;
        push_node(next_node);
    };
    void push_node(Node *next_node) {
        if ( head == 0 ) {
            head = next_node;
        } else{
            Node *current = head;
            for (Node *ptr = head; ptr != 0; ptr = ptr->get_next_node()) {
                current = ptr;
            }
            current->set_next_node(next_node);
        }
    }
    void print() {
        Node *current = head;
        cout << endl << "결과를 출력합니다" << endl;
        for (Node *ptr = head; ptr != 0; ptr = ptr->get_next_node()) {
            current = ptr;
            cout << current->get_value() << " ";
        }
    }
    void print_file(string dir_path, string file_name) {
        ofstream outFile(dir_path + file_name);
        Node *current = head;

        if ( head == 0 ) {
            outFile << "0";
        } else {
            for (Node *ptr = head; ptr != 0; ptr = ptr->get_next_node()) {
                current = ptr;
                if (current != head) {
                    outFile << " ";
                }
                outFile << current->get_value();
            }
        }

        outFile.close();
    }
};

Numbers ReadNumbers(string dir_path, string file_name);
void printNumbers(Numbers numbers);
void InsertionSort(Numbers numbers);
LinkedList FindSquareNumber(Numbers target_numbers);

int main() {
    Numbers numbers;
    // 제일 처음 제시된 숫자 이상으로 값이 더 추가될 일이 없음
    // 정렬은 딱 한번만 하면 된다.
    // 각 원소 접근은 제곲수를 찾기위해 빈번하게 일어난다.
    // 배열, 링크드리스트, 트리

    // 1. 파일 입력 받기
    numbers = ReadNumbers("./", "square.inp");

    // 2. 입력 받은 수 정렬
    InsertionSort(numbers);

    // 3. 제곱수 찾기
    LinkedList square_number_list = FindSquareNumber(numbers);

    // 4. 파일 출력 하기
    square_number_list.print_file("./", "square.out");

    return 0;
}

Numbers ReadNumbers(string dir_path, string file_name) {
    ifstream openFile(dir_path + file_name);
    string line;
    int line_count = 0;
    int number_count = 0;
    int *numbers = 0;

    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            line_count++;
            if (line_count == 1) {
                string buf_1;
                stringstream ss(line);

                while (ss >> buf_1) {
                    number_count = stoi(buf_1);
                }
                numbers = new int[number_count];
                continue;
            }

            if (line_count == 2) {
                string buf_1;
                stringstream ss(line);
                int i = 0;
                while (ss >> buf_1) {
                    numbers[i] = stoi(buf_1);
                    i++;
                }
                continue;
            }
        }
        openFile.close();
    }

    return Numbers(numbers, number_count);
}

void InsertionSort(Numbers target) {
    int count = target.get_number_count();
    int *target_numbers = target.get_numbers();

    for (int i = 1; i < count; i++) {
        int value = target_numbers[i];
        int j = i - 1;

        while(j >= 0 && value < target_numbers[j]) {
            target_numbers[j + 1] = target_numbers[j];
            j--;
        }
        target_numbers[j + 1] = value;
    }

    target.set_numbers(target_numbers);
}

void printNumbers(Numbers numbers) {
    int count = numbers.get_number_count();
    int *target_numbers = numbers.get_numbers();
    for (int i = 0; i < count; i++) {
        cout << target_numbers[i] << " ";
    }
}

LinkedList FindSquareNumber(Numbers target) {
    int count = target.get_number_count();
    int *target_numbers = target.get_numbers();
    LinkedList linked_list;

    for (int i = 2; i < count; i++) {
        int testing_number = target_numbers[i];
        int minimum_index = 0;
        int maximum_index = i - 1;
        int square_root_value = (int) sqrt((double) testing_number);
        int sum = 0;

        while(minimum_index != maximum_index) {

            if (target_numbers[maximum_index] > square_root_value) {
                maximum_index--;
                continue;
            } else {
                sum = (target_numbers[minimum_index] * target_numbers[minimum_index]) + (target_numbers[maximum_index] * target_numbers[maximum_index]);
            }
            if (sum == testing_number) {
                linked_list.push_node(new Node(testing_number));
                break;
            } else if (sum > testing_number) {
                maximum_index--;
            } else if (sum < testing_number) {
                minimum_index++;
            }
        }
    }

    return linked_list;
}