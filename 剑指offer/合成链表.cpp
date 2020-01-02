#include<iostream>
using namespace std;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
/*非递归法*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1==NULL)
            return pHead2;
        if(pHead2==NULL)
            return pHead1;
        ListNode* Head;
        ListNode* p;
        //取较小值作头结点
        if(pHead1->val<=pHead2->val){
            Head=pHead1;
            pHead1=pHead1->next;
        }
        else{
            Head=pHead2;
            pHead2=pHead2->next;
        }  
        //开始遍历合并
        p=Head;                                                   //p为合并后的链表的工作指针
        while(pHead1!=NULL&&pHead2!=NULL){                       //当有一个链表到结尾时，循环结束
            if(pHead1->val<=pHead2->val){          //如果链表1的结点小于链表2的结点
                p->next=pHead1;                            //取这个结点加入合并链表
                pHead1=pHead1->next;                 //链表1后移一位
                p=p->next;                                      //工作指针后移一位
            }               
            else{                                               //否则取链表2的结点
                p->next=pHead2;
                pHead2=pHead2->next;
                p=p->next;
            }                
        }
        if(pHead1 == NULL)           //链表1遍历完了
            p->next = pHead2;         //如果链表2也遍历完了，则pHead2=NULL
        if(pHead2 == NULL)            //链表2遍历完了
            p->next = pHead1;         ///如果链表1也遍历完了，则pHead1=NULL
        return Head;
    }
};

/*递归法*/
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