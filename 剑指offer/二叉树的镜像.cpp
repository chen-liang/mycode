/*
���������Ķ�����������任ΪԴ�������ľ���
�������ľ����壺Դ������ 
    	    8
    	   /  \
    	  6   10
    	 / \  / \
    	5  7 9 11
    	���������
    	    8
    	   /  \
    	  10   6
    	 / \  / \
    	11 9 7  5
*/
#include<iostream>
#include<stack>
using namespace std;
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
//�ݹ鷨
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot==NULL) return;
        
        TreeNode* temp=NULL;
         temp=pRoot->right;
         pRoot->right=pRoot->left;
         pRoot->left=temp;
         Mirror(pRoot->left);
         Mirror(pRoot->right);
    }
};
//�ǵݹ鷨
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot==NULL) return;
        stack<TreeNode*> stackNode;
        stackNode.push(pRoot);
        while(stackNode.size())
        {     
          TreeNode* pRoot1=stackNode.top();
          stackNode.pop();
          if(pRoot1->left!=NULL||pRoot1->right!=NULL)
          {
              TreeNode* temp=pRoot1->right;
             pRoot1->right=pRoot1->left;
             pRoot1->left=temp;
          }
          if(pRoot1->left!=NULL) stackNode.push(pRoot1->left);
          if(pRoot1->right!=NULL) stackNode.push(pRoot1->right);
    }
    } 
}; 