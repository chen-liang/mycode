#include<vector>
#include<stack>
using namespace std;
/*
stack��ջ��һ���Ƚ���������Ա�
����Ԫ��ֻ���ڱ��һ�ν��С�����Ԫ�ص�һ�˳�Ϊջ����
��һ�˳�Ϊջ�ס�����Ԫ�ؽ���ջ��ɾ��Ԫ�ؽг�ջ��
s.push();//��ջ 
s.top(); //����ջ��Ԫ��    
s.pop();//��ջ 
s.size();//����ջ��Ԫ�ظ���   

s.empty();//�ж�ջ�Ƿ�Ϊ�գ�Ϊ�շ���true����Ϊ�շ���false   
//ջ�����   
while(!s.empty())// ջ��Ϊ��   
{  
    s.pop();//��ջ   
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
