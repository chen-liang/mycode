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
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        ListNode* pNode=NULL ;
        if(pHead1==NULL)
            return pHead2;
        else if(pHead2==NULL)
            return pHead1;
        if(pHead1->val<pHead2->val)
        {
            pNode=pHead1;
            pNode->next=Merge(pHead1->next,pHead2);
        }
        else 
        {
            pNode=pHead2;
            pNode->next=Merge(pHead1,pHead2->next);
        }
    
        return pNode;
    }
};