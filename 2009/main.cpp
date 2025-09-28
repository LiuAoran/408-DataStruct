#include <algorithm>
#include <iostream>
#include <vector>
/*
 *已知一个带头结点的单链表，节点结构为
 *  |    data    |    Link    |
 *  假设该链表只给出了头指针 list。
 *  在不改变链表的前提下，
 *  设计尽可能高效的算法，
 *  查找链表中倒数第 k 个位置上的节点（k为正整数），
 *  查找成功，输出 data 域的值，并返回 1，
 *  否则，只返回 0。
 */

/*
 * 基本设计思想：
 * 定义指针 p、q，初始时均指向头节点的下一节点。
 * p 指针沿链表移动；
 * 当 p 指针移动到第 k 个节点时，
 * q 指针开始与 p 指针同步移动
 * p 指针移动到最末端节点时，
 * q指针此时移动到倒数第 k 个节点
 */

#define FAILURE 0

struct  LNode {
    int data;
    struct LNode* link = nullptr;
};

using  LINKLIST = LNode*;

void AddNode(LINKLIST &link_list, std::vector<int> values) {
    for (int value : values) {
        LINKLIST new_node = new LNode{
            .data = value,
            .link = nullptr
        };
        if (link_list == nullptr) {
            link_list = new LNode{
                .link = new_node
            };
        }
        else {
            LINKLIST temp_list = link_list;
            while (temp_list->link != nullptr) {
                temp_list = temp_list->link;
            }
            temp_list->link = new_node;
        }
    }
}

int FindNthFromEnd(LINKLIST linklist, int n_th) {
    LINKLIST pNode = linklist->link;
    LINKLIST qNode = linklist->link;
    int count = 0;
    while (pNode != nullptr) {
        if (count < n_th) {
            count = count + 1;
        }else {
            qNode = qNode->link;
        }
        pNode = pNode->link;
    }
    if (count < n_th) {
        return FAILURE;
    }
    else {
        return qNode->data;
    }
}

int main() {
    LINKLIST NodeList = nullptr;
    int key = 6;
    std::vector<int> values{
        1,2,3,4,5,6
    };
    AddNode(NodeList, values);
    std::cout << FindNthFromEnd(NodeList, key) << std::endl ;
    delete NodeList;
    return 0;
}