#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

class Task {
private:
    int id;
    int begin;
    int end;
    int cost;
    int working_day;
public:
    Task() {}
    Task(int id, int begin, int end, int cost, int working_day) : id(id), begin(begin), end(end), cost(cost), working_day(working_day) {}

    int get_begin() const { return begin; }
    int get_end() const { return end; }
    int get_cost() const { return cost; }
    int get_working_day() const { return working_day; }
    void set_ibec(int id, int begin, int end, int cost, int working_day) {
        this->id = id;
        this->begin = begin;
        this->end = end;
        this->cost = cost;
        this->working_day = working_day;
    }
    void set_becw(int begin, int end, int cost, int working_day) {
        this->begin = begin;
        this->end = end;
        this->cost = cost;
        this->working_day = working_day;
    }
    friend bool operator< (const Task& lhs, const Task& rhs) {
        return lhs.id < rhs.id;
    }
};

class Schedule {
private:
    int count;
    Task* tasks;
public:
    Schedule() {};
    Schedule(int count, Task *tasks) : count(count), tasks(tasks) {}

    int get_count() const { return count; }
    Task *get_tasks() const { return tasks; }
};

class Choice {
private:
    int profit;
    int working_day;
public:
    Choice() {}
    Choice(int profit, int working_day) : profit(profit),
                                          working_day(working_day) {}
    Choice(const Choice &choice) {
        profit = choice.get_profit();
        working_day = choice.get_working_day();
    }
    int get_profit() const { return profit; }
    int get_working_day() const { return working_day; }
    void set_pw(int profit, int working_day) {
        this->profit = profit;
        this->working_day = working_day;
    }
};

Schedule ReadTasks(string dir_path, string file_name);
void InsertionSort(Schedule target, int count);
void PrintFile(string dir_path, string file_name, Choice choice);
Choice GetCurrentTaskIncludedChoice(int task_count, Task current_task, Choice *before_result);
Choice GetBetterChoice(Choice a, Choice b);

int main() {
    Schedule schedule;

    // 1. 파일 입력 받기
    schedule = ReadTasks("./", "freelance.inp");

    // 정렬하기
    int count = schedule.get_count();
    InsertionSort(schedule, count);

    // 2. 최선의 선택하기
    Task *tasks = schedule.get_tasks();
    Choice* best_choice = new Choice[count];

    best_choice[0].set_pw(tasks[0].get_cost(), tasks[0].get_working_day());
    for (int i = 1; i < count; i++) {
        set<Task> temp_schedule;

        int begin = tasks[i].get_begin();
        int end = tasks[i].get_end();
        for (int j = 0; j < i; j++) {
            if (tasks[j].get_end() < begin || tasks[j].get_begin() > end) {
                temp_schedule.insert(tasks[j]);
            }
        }

        int task_count = (int) temp_schedule.size();
        Choice temp = GetCurrentTaskIncludedChoice(task_count, tasks[i], best_choice);
        best_choice[i] = GetBetterChoice(best_choice[i - 1], temp);
    }

    // 3. 파일 출력 하기
    PrintFile("./", "freelance.out", best_choice[count - 1]);
    return 0;
}

Schedule ReadTasks(string dir_path, string file_name) {
    ifstream openFile(dir_path + file_name);
    string line;
    int line_count = 0;
    Task *tasks = 0;
    int task_count = 0;

    if (openFile.is_open()) {
        int i = 0;
        while (getline(openFile, line)) {
            line_count++;
            string buf_1;
            stringstream ss(line);

            if (line_count == 1) {
                while (ss >> buf_1) {
                    task_count = stoi(buf_1);
                }
                tasks = new Task[task_count];
                continue;
            }
            string buf_2;
            string buf_3;

            while (ss >> buf_1 && ss >> buf_2 && ss >> buf_3) {
                tasks[i].set_ibec(i, stoi(buf_1), stoi(buf_2), stoi(buf_3), stoi(buf_2) - stoi(buf_1) + 1);
                i++;
            }
        }
        openFile.close();
    }

    return Schedule(task_count, tasks);
}

void InsertionSort(Schedule schedule, int count) {
    Task *target = schedule.get_tasks();

    for (int i = 1; i < count; i++) {
        Task value = target[i];
        int j = i - 1;

        while(j >= 0 && value.get_end() < target[j].get_end()) {
            target[j + 1].set_becw(target[j].get_begin(), target[j].get_end(), target[j].get_cost(), target[j].get_working_day());
            j--;
        }
        target[j + 1].set_becw(value.get_begin(), value.get_end(), value.get_cost(), value.get_working_day());
    }
}

Choice GetCurrentTaskIncludedChoice(int task_count, Task current_task, Choice *before_result) {
    if (task_count == 0) {
        return Choice(current_task.get_cost(), current_task.get_working_day());
    } else {
        return Choice(before_result[task_count - 1].get_profit() + current_task.get_cost() - 10,
                      before_result[task_count - 1].get_working_day() + current_task.get_working_day());
    }
}

Choice GetBetterChoice(Choice a, Choice b) {
    if (a.get_profit() > b.get_profit()) {
        return a;
    } else if (a.get_profit() == b.get_profit()) {
        if (a.get_working_day() > b.get_working_day()) {
            return b;
        } else {
            return a;
        }
    } else {
        return b;
    }
}

void PrintFile(string dir_path, string file_name, Choice choice) {
    ofstream outFile(dir_path + file_name);
    outFile << choice.get_profit() << " " << choice.get_working_day();
    outFile.close();
}
