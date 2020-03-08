/*
输入一个链表，反转链表后，输出新链表的表头。
http://blog.csdn.net/qq_36472818/article/details/96379507
*/
#include<iostream>
using namespace std;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode* pNode=pHead;
        ListNode* pre=NULL;
        ListNode* temp=NULL;
        while(pNode!=NULL)
        {
            temp=pre;
            pre=pNode;
            pNode=pNode->next;
            pre->next=temp;
        }        
        return pre;
    }
};