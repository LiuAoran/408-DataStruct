//
// Created by Administrator on 2025/10/2.
//

#include "Sort.h"

/*
 *时间复杂度：
 *最好情况（数组已经有序）：O(n)
 *最坏情况（数组逆序）：O(n²)
 *平均情况：O(n²)
 *空间复杂度：O(1)
 *特点：
 *简单，稳定排序
 *对小规模或部分有序数组效率高
 */
void InsertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int temp = arr[i];
        int j = i - 1;

        // 将 arr[i] 插入到已经排序的部分
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j]; // 将元素向右移动
            j--;
        }

        // j 每次跳动后指向的是即将比对的位置，插入元素到 j + 1
        arr[j + 1] = temp;
    }
}

/*
* 时间复杂度：
* 查找位置：O(log n)
* 移动元素：O(n)
* 所以总时间复杂度：O(n²)
* 最好情况：O(n)（数组已排序，移动最少）
* 空间复杂度：O(1)
* 特点：
* 减少了比较次数，但移动次数不变
* 对大数组优化不大
* 稳定排序
 */
void HalfInsertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int temp = arr[i];
        int low = 0;
        int high = i - 1;
        int mid = 0;
        // 将 arr[i] 插入已排序部分
        while (low <= high) {
            mid = (high + low) / 2;
            if (temp > arr[mid]) {
                low = mid + 1;
            } else if (temp < arr[mid]) {
                high = mid - 1;
            }
        }
        /*
         *为什么插入 low 所在位置
         *
         *arr = [2, 4, 6, 8], temp = 5
         *i = 4
         *
         *low=0, high=3, mid=1 → arr[mid]=4
         *temp>4 → low=mid+1=2
         *
         *low=2, high=3, mid=2 → arr[mid]=6
         *
         *temp<6 → high=mid-1=1
         *
         *循环结束：
         *
         *low=2, high=1,退出，即最终会找到比 temp 大的一个 low
         *插入位置和 mid 没关系
         */
        for (int j = i - 1; j >= low; j--) {
            arr[j + 1] = arr[j];
        }
        arr[low] = temp;
    }
}

/*
 *时间复杂度（与 gap 序列有关）：
 *最坏情况：依 gap 不同而不同
 *原始 Shell 序列（gap=n/2,n/4,…,1）：O(n²)
 *Hibbard 序列（1,3,7,…）：O(n^(3/2))
 *Sedgewick 序列：O(n^(4/3))
 *最佳复杂度可以接近 O(n log n)
 *平均情况：约 O(n^(1.25)~n^(1.5))
 *最好情况（基本有序）：O(n log n)
 *空间复杂度：O(1)
 *特点：
 *不稳定排序
 *对大规模数组比普通插入排序快很多
 *移动次数减少是主要优化
 *
 * gap 从数组长度开始，每次 /2 的希尔排序。
 * 里面用的是直接插入
 * 在希尔排序里，每组的元素本身是 间隔的子序列，它们并不是连续的数组，因此：
 * 可以用二分找到插入位置，但元素的移动还是按 gap 间隔来做
 * 移动的操作并不比普通插入少多少（因为 gap 较大时移动的元素更远）
 * 二分插入只优化了查找位置，但移动元素仍然是 O(n) 级别，对希尔排序加速作用有限。
 */
void ShellSort(int arr[], int length) {
    for (int gap = length / 2; gap >= 1; gap /= 2) {
        for (int i = gap; i < length; i += 1) {
            int temp = arr[i];
            int j = i - gap;
            while (j >= 0 && temp < arr[j]) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = temp;
        }
    }
}
