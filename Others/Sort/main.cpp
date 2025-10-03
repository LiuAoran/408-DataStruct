#include <iostream>
#include "Sort.h"

void PrintArray(int arr[], int length) {
    int i = 0;
    while (i < length) {
        std::cout << arr[i] << " ";
        i++;
    }
}

int main() {
    int arr[12] = {7, 3, 10, 2, 6, 9, 4, 12, 1, 5, 8, 11};
    ShellSort(arr, 12);
    PrintArray(arr, 12);
    return 0;
}
