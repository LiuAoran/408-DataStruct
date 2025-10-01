#include <iostream>
#include <vector>

#define MAXLENGTH 255

struct KMPString {
    char c[MAXLENGTH] = {};
    int length = 0;
};

// 代码假设数组下标从 1 开始

void CreateNextVal(KMPString str, int next[]) {
    int i = 1, j = 0;
    next[1] = 0;
    while (i < str.length) {
        if (j == 0 || str.c[i] == str.c[j]) {
            i++;
            j++;
            if (str.c[i] != str.c[j]) {
                next[i] = j;
            } else {
                next[i] = next[j];
            }
        } else {
            j = next[j];
        }
    }
}

void CreateNextArr(KMPString str, int next[]) {
    int i = 1, j = 0; // i 指向当前要计算 next 值的位置，j 表示当前前缀长度
    next[1] = 0; // 按惯例，模式串第一个字符的 next 值为 -1
    while (i < str.length) {
        if (j <= 0 || str.c[i] == str.c[j]) {
            // 如果当前字符匹配，或者 j 已经回到 0
            i++;
            j++;
            // 记录当前位置的 next 值
            next[i] = j;
        } else {
            // 如果不匹配，则回退 j
            j = next[j];
        }
    }
    CreateNextVal(str, next);
}



int KMPFindIndex(KMPString main, KMPString sub, int next[]) {
    int i = 1; // i 指向主串 current 字符的位置（注意这里假设下标从 1 开始）
    int j = 1; // j 指向模式串 current 字符的位置（下标从 1 开始）

    // 当主串和模式串都没到末尾时循环匹配
    while (i <= main.length && j <= sub.length) {
        if (j == 0 || main.c[i] == sub.c[j]) {
            // 如果 j == 0 表示模式串回退到开头，可以直接移动主串
            // 或者主串和模式串当前字符匹配，则同时向右移动
            i++; // 主串指针右移
            j++; // 模式串指针右移
        } else {
            // 当前字符不匹配，则模式串指针回退到 next[j]，利用前缀信息避免重复比较
            j = next[j];
        }
    }

    // 如果模式串指针走到了末尾，说明匹配成功
    if (j > sub.length) {
        // 返回匹配在主串中的起始位置（根据下标规则）
        return i - sub.length;
    }

    // 匹配失败
    return 0;
}


int main() {
    KMPString sub{
        .c = {' ', 'a', 'a', 'a', 'a', 'b'},
        .length = 5
    };
    KMPString main{
        .c = {' ', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'a', 'b'},
        .length = 9
    };

    int next[5];

    CreateNextArr(sub, next);
    std::cout << KMPFindIndex(main, sub, next) << std::endl;
    return 0;
}
