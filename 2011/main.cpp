 #include <iostream>
/*
 *一个长度为 L(L>=1) 的升序序列 S，处在第 Ceiling(L/2) 位的数称为 S 的中位数。
 *例如，若序列 S1 = （11，13，15，17，19）
 *则 S1 的中位数是 15
 *两个序列的中位数是含他们所有元素的升序序列的中位数。
 *例如 S2 = (2,4,6,8,10),则 S1,S2的中位数是11
 *现有两个等长升序序列 A 和 B，试设计一个在时间和空间两方面都尽可能高效的算法
 *找出两个序列 A 和 B 的中位数
 */

/*
 *基本设计思想：
 *则 取中位数 mid = n
 *设置两个参数 p,q，分别对应 序列中当前指向的位置
 *设置counter位初始为0，每次 +1 同时比对 p,q 指向的数字，谁小则向后移动一位，直到 counter ==  mid-1
 *最后找两个数字，谁小选谁
 *
 *O(n)
 *
 */
int GetMiddleEasy(int arr_a[], int arr_b[], int arr_size) {
    int p = 0, q = 0;
    for (int i = 0; i < arr_size-1; i++) {
        if (arr_a[p] >= arr_b[q]) {
            q++;
        }else {
            p++;
        }
    }
    return arr_a[p] < arr_b[q]?arr_a[p] :arr_b[q];
}

/*
 *基本设计思想：
 *对两个数组 arr_a 和 arr_b,
 *若中位数 a < b
 *则对归并排序后的 arr_mix 有...a..b..
 *中位数在 a, b 之间
 *直接找到 a,b 各自中位数
 *比较后抛弃小的一方前面的，大的一方后面的
 *例如 a：1，3，5，7，9，100
 *b : 2,4,6,8,10，99
 *变为：
 *7，9，100
 *2，4，6
 *最后是
 *7，9
 *4，6
 *-
 *7
 *6
 *
 *选择 6
 *
 * O(log2n) 苹果方法
 * 难写一点
 */
int GetMiddleBetter(int arr_a[], int arr_b[], int arr_size) {
    int begin_a = 0,begin_b = 0;
    int end_a = arr_size - 1,end_b = arr_size - 1;
    while (begin_a != end_a) {
        int mid_a = (end_a + begin_a) / 2;
        int mid_b = (end_b + begin_b) / 2;
        if (arr_a[mid_a] == arr_b[mid_b]) {
            return  arr_a[mid_a];
        }
        if (arr_a[mid_a] > arr_b[mid_b]) {
            if ((end_a - begin_a)%2 == 0) {
                begin_b = mid_b;
                end_a = mid_a;
            }else {
                begin_b = mid_b + 1;
                end_a = mid_a;
            }
        }else {
            if ((end_a - begin_a)%2 == 0) {
                begin_a = mid_a;
                end_b = mid_b;
            }else {
                begin_a = mid_a +1;
                end_b = mid_b;
            }
        }
    }
    return arr_a[begin_a]<arr_b[begin_b]?arr_a[begin_a]:arr_b[begin_b];
}


int main() {
    int arr_a[6] = {1,3,5,7,9};
    int arr_b[6] = {2,4,6,8,10};
    std::cout << GetMiddleBetter(arr_a, arr_b, 5)<<std::endl;
    return 0;
}