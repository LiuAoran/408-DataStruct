#include <algorithm>
#include <iostream>
#include <vector>

/*
 *设将 n(n>1) 个整数存放到一维数组 R 中，
 *试设计一个在时间和空间两方面都尽可能高效的算法，
 *将 R 中保存的序列循环左移 p(0<p<n) 个位置，
 *即将 R 中的数据由 (x0, x1, x2...xn-1) 变换为 (xp, xp+1...xn-1, x0, x1...xp-1)
*/

/*
 *基本设计思想：
 * x0, x1, x2...xp, xp+1...xn-1
 * 倒转后变为
 * xn-1, xn-2...xp+1,xp...x2,x1,x0
 * 再分别对 xn-1, xn-2...xp+1,xp 和 xp-1...x2,x1,x0 倒转
 */

/*
 * 时间复杂度 O(n): 倒置数组
 * 空间复杂度 O(1): 原地工作
 */

//循环一个变量很难写时可以搞两个，左右同时逼近
void Reverse(int arr[], int left_edge,int right_edge) {
    while ( left_edge < right_edge ) {
        int temp = arr[left_edge];
        arr[left_edge] = arr[right_edge];
        arr[right_edge] = temp;
        left_edge ++;
        right_edge --;
    }
}

void LeftRotate(int arr[], int arr_len,int key) {
    Reverse(arr, 0, arr_len - 1);
    Reverse(arr, 0, key - 1);
    Reverse(arr, key, arr_len - 1);
}

int main() {
    int key = 2;
    /*
    std::vector<int> vec{
        0,1,2,3,4,5,6,7,8,9
    };[5] = {int} 2
    std::rotate(arr.begin(), arr.end()-3, arr.end());
    for (const int arr1: vec) {
        std::cout << arr1 << std::endl;
    }
    */
    int arr[] = {1,2,3,4,5,6,7};
    int arr_len = 7;
    LeftRotate(arr,arr_len, key);

    return 0;
}