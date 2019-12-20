#include<vector>
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
    vector<int> printListFromTailToHead(ListNode* head) {
        ListNode *p;
        p=head;
        stack<int> s;
        
        while(p!=NULL)
        {
            s.push(p->val);
            p=p->next;
        }
        vector<int> value;
        while(!s.empty())
        {
            value.push_back(s.top());
            s.pop();
        }
        return value;
    }
};