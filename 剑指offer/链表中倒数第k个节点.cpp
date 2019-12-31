#include<stack>
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
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(pListHead==NULL||k==0) return NULL;
        ListNode *p=pListHead;
        stack<ListNode*> s;
        while(p!=NULL)
        {
            s.push(p);
            p=p->next;
        }
       if (s.size() < k) {
            return NULL;
        }
        for(int i=0;i<k-1;i++)
        {
            s.pop();
        }
        return s.top();
    
    }
};