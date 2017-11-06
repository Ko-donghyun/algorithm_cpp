#include <iostream>
#include "oil.h"

using namespace std;

int main() {
    initial();
    int i = -1, j = -1;
    int n = oil_size() - 1;

    int start = 0;
    int end = n;

    while (i < 0 || j < 0) {
        int half = start + (end - start) / 2;
        int left = observe(start, half);
        int right = observe(half + 1, end);

        if (left == 0) {
            if (right == 1) {
                if (i < 0) { i = half + 1; }
                if (j < 0) { j = end; }
            } else if (right == 2) {
                start = half + 1;
            }
        } else if (left == 1) {
            if (right == 0) {
                if (i < 0) { i = start; }
                if (j < 0) { j = half; }
            } else if (right == 1) {
                if (i < 0) { i = start; }
                if (j < 0) { j = end; }
            } else if (right == 2) {
                if (i < 0) { i = start; }
                start = half + 1;
            }
        }  else if (left == 2) {
            if (right == 0) {
                end = half;
            } else if (right == 1) {
                if (j < 0) { j = end; }
                end = half;
            } else if (right == 2) {
                // 왼쪽의 start index 변경

                int left_end = half - 1;
                int temp_start = start + 1;
                int left_start = temp_start + (left_end - temp_start) / 2;
                while (i < 0) {
                    left = observe(left_start, left_end);
                    if (left <= 0) {
                        i = left_end + 1;
                    } else if (left == 1) {
                        left_end = left_start - 1;
                        left_start = temp_start;
                    } else if (left == 2) {
                        left_end = left_end - 1;
                        temp_start = left_start;
                        left_start = left_start + (left_end - left_start) / 2;
                    }
                }

                // 오른쪽의 end index 변경
                int right_start = half + 2;
                int temp_end = end - 1;
                int right_end = temp_end - (temp_end - right_start) / 2;
                while (j < 0) {
                    right = observe(right_start, right_end);
                    if (right <= 0) {
                        j = right_start - 1;
                    } else if (right == 1) {
                        right_start = right_end + 1;
                        right_end = temp_end;
                    } else if (right == 2) {
                        right_start = right_start + 1;
                        temp_end = right_end;
                        right_end = right_end - (right_end - right_start) / 2;
                    }
                }
            }
        }
    }

    oil_report(i, j);
    return 0;
}
