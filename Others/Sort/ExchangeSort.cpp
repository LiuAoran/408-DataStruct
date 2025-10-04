//
// Created by Administrator on 2025/10/2.
//

#include "Sort.h"
/*
 * 时间复杂度：
 * 最坏情况（完全逆序）：O(n²)
 * 平均情况：O(n²)
 * 最好情况（已经有序）：O(n)
 * 空间复杂度：O(1)
 *
 * 特点：
 * - 稳定排序
 * - 简单直观，但大规模数组效率低
 * - 可以通过提前退出优化（如果一轮没有交换，则数组已排序）
 *
 * 原理：
 * 每次从头到尾比较相邻元素，把大的“冒泡”到末尾
 * 外层循环控制轮数，内层循环完成每轮冒泡
 */
void BubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool is_exchanged = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                is_exchanged = true;
            }
        }
        if (!is_exchanged) {
            return;
        }
    }
}

// ---------------- 分区函数 ----------------
int Partition(int arr[], int low, int high) {
    int pivox = arr[low]; // 1️⃣ 选择基准 pivot，这里选择当前子数组的第一个元素
    //    pivox 的值将会被暂存，最后放回正确位置

    while (low < high) { // 2️⃣ 当 low 与 high 没有交错时，继续移动指针

        // 从右向左找第一个小于 pivot 的元素
        while (low < high && arr[high] >= pivox) {
            high--; // high 指针向左移动，跳过大于等于 pivot 的元素
        }
        arr[low] = arr[high]; // 找到比 pivot 小的元素，填到左边的坑里

        // 从左向右找第一个大于 pivot 的元素
        while (low < high && arr[low] <= pivox) {
            low++; // low 指针向右移动，跳过小于等于 pivot 的元素
        }
        arr[high] = arr[low]; // 找到比 pivot 大的元素，填到右边的坑里
    }

    arr[low] = pivox; // 3️⃣ 当 low == high 时，把 pivot 放回最终位置
    //    此时 pivot 左边都比它小，右边都比它大

    return low; // 4️⃣ 返回 pivot 的最终位置
}

// ---------------- 快排核心函数（递归） ----------------
void QuickSortCore(int arr[], int low, int high) {
    if (low < high) { // 递归终止条件：子数组长度 ≤ 1 时停止
        int pivot_pos = Partition(arr, low, high); // 分区，返回 pivot 最终位置

        // 递归排序 pivot 左边的子数组
        QuickSortCore(arr, low, pivot_pos - 1);

        // 递归排序 pivot 右边的子数组
        QuickSortCore(arr, pivot_pos + 1, high);
    }
}

// ---------------- 快排接口函数 ----------------
/*
 * 时间复杂度：
 * 最坏情况（数组已排序，选第一个/最后一个为 pivot）：O(n²)
 * 平均情况：O(n log n)
 * 最好情况（每次 pivot 恰好在中间）：O(n log n)
 * 空间复杂度：
 * - 原地排序：O(log n) 递归栈
 *
 * 特点：
 * - 不稳定排序
 * - 对大规模数组非常快
 * - 原地排序，不需要额外数组
 *
 * 原理：
 * - 选择 pivot（基准）
 * - 将数组分为左右两部分：左边 < pivot，右边 > pivot
 * - 递归排序左右两边
 *
 * 分区方法（常用“挖坑法”或双指针法）：
 * - 暂存 pivot
 * - 左右指针交替移动填坑
 * - pivot 放回正确位置
 *
 * 注意：
 * - pivot 的选择影响最坏时间复杂度
 * - 随机选择或三数取中可以减少最坏情况概率
 */
void QuickSort(int arr[], int length) {
    QuickSortCore(arr, 0, length - 1); // 对整个数组进行快速排序
}
