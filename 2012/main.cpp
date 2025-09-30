#include <iostream>
#include <vector>
/*
 *假定采用带头结点的单链表保存单词，
 *当两个单词有相同后缀时，可以共享后缀存储空间
 *例如“loading”和“being”
 *
 *Head1 -> [ l ] -> [ o ] -> [ a ] -> [ d ] \
 *                                           \
 *                                            -> [ i ] -> [ n ] -> [ g ] -> nullptr
 *                                           /     ^
 *Head2 -> [ b ] -> [ e ] ------------------/      p
 *
 *设 str1 和 str2 分别指向两个单词所在单链表的头节点，
 *链表结构为 | data | next |
 *请设计一个时间上看上去尽可能高效的算法
 *找出 str1 和 str2 所指的两个链表共同后缀的起始位置,示意图中 i字符所在的节点位置 p
 */

#pragma region Preparation
struct WordNode {
    char letter{};
    WordNode* next = nullptr;
};

using WordList = WordNode*;

void AddNode(WordList &word_list, std::vector<char> chars) {
    if (word_list == nullptr) {
        word_list = new WordNode;
    }
    for (char letter : chars){
        WordNode* temp_node = word_list;
        WordNode* new_node = new WordNode{
             .letter = letter
         };
        while (temp_node->next != nullptr) {
            temp_node = temp_node->next;
        }
        temp_node->next = new_node;
    }
}

void AddSharedNode(WordList &word_list_a, WordList &word_list_b, std::vector<char> chars) {
    if (word_list_a == nullptr) {
        word_list_a = new WordNode;
    }
    if (word_list_b == nullptr) {
        word_list_b = new WordNode;
    }
    for (char letter : chars) {
        WordNode* shard_node = new WordNode{
            .letter = letter
        };
        WordNode* temp_node_a = word_list_a;
        WordNode* temp_node_b = word_list_b;
        while (temp_node_a->next != nullptr) {
            temp_node_a = temp_node_a->next;
        }
        while (temp_node_b->next != nullptr) {
            temp_node_b = temp_node_b->next;
        }
        temp_node_a->next = shard_node;
        temp_node_b->next = shard_node;
    }
}
#pragma endregion

/*
 *基本设计思想：
 *定义指针 p, q 分别指向两个链表的头节点
 *计算并比较两个链表的长度
 *较短链表的指针不动，较长链表的指针向后移动两链表长度的差值，
 *使两个指针从后往前数经过的节点数相同。
 *两个指针同时向后移动，每次移动都比对指向的节点，若相同则返回指针p所在位置。
 */
int CalcListLength(WordList word_list) {
    int counter = 0;
    WordList temp_list = word_list -> next;//去掉头节点
    while (temp_list != nullptr) {
        counter++;
        temp_list = temp_list->next;
    }
    return  counter;
}

WordNode* FindPublicSuffix(WordList word_list_a, WordList word_list_b) {
    int a_length = CalcListLength(word_list_a);
    int b_length = CalcListLength(word_list_b);
    WordNode* p = word_list_a->next;
    WordNode* q = word_list_b->next;
    int difference = abs(a_length - b_length);
    if (a_length > b_length) {
        while (difference--) {
            p = p->next;
        }
    }else {
        while (difference--) {
            q = q->next;
        }
    }
    while (p != nullptr) {
        if (p == q) {
            return  p;
        }
            p = p->next;
            q = q->next;
    }
    return  nullptr;
}

int main() {
    WordList word_list_a = nullptr;
    WordList word_list_b = nullptr;

    AddNode(word_list_a, std::vector<char>{'l','o','a','d'});
    AddNode(word_list_b, std::vector<char>{'b','e'});
    AddSharedNode(word_list_a, word_list_b, std::vector<char>{'i','n','g'});
    WordNode* node = FindPublicSuffix(word_list_a, word_list_b);

    return 0;
}