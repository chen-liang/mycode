#include<vector>
#include<stack>
using namespace std;
/*
stack堆栈是一个先进后出的线性表，
插入元素只能在表的一段进行。插入元素的一端称为栈顶，
另一端称为栈底。插入元素叫入栈，删除元素叫出栈。
s.push();//入栈 
s.top(); //返回栈顶元素    
s.pop();//出栈 
s.size();//返回栈中元素个数   

s.empty();//判断栈是否为空，为空返回true，不为空返回false   
//栈的清空   
while(!s.empty())// 栈不为空   
{  
    s.pop();//出栈   
} 
*/
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
