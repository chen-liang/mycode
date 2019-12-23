#include<iostream>
using namespace std;
struct TreeNode{
    char ch;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x):ch(x),left(NULL),right(NULL){}
};
TreeNode *create(TreeNode *T)
{
    char ch;
    cin>>ch;
    if(ch=='#') T=NULL;
    else 
    {
        T=(TreeNode *)malloc(sizeof(TreeNode));
        T->ch=ch;
        create(T->left);
        create(T->right);
        return T;
    }
    
    return NULL;
}
int main(void)
{
    TreeNode *Tree;
    create(Tree);
    return 0;
}