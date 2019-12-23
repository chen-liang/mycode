#include<iostream>
#include<malloc.h>
using namespace std;
struct TreeNode{
    char ch;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x):ch(x),left(NULL),right(NULL){}
};
//树的创建
void create(TreeNode * &T)
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
    }
}
/*
BinaryTreeNode * CreateBinaryTree2()
{
    BinaryTreeNode *T;
 
    char data;
    cin>>data; // scanf();
 
    if(data=='#')
        T=NULL;
    else
    {
        T= new BinaryTreeNode;//(BinaryTreeNode *)malloc(sizeof(BinaryTreeNode))
        T->value=data;
 
        T->left=CreateBinaryTree2();
        T->right=CreateBinaryTree2();
    }
 
    return T;
}
*/
//递归前序、中序、后序遍历
void PreOrder(TreeNode *T)
{
    if(T==NULL) return;
    cout<<T->ch<<" ";
    PreOrder(T->left);
    PreOrder(T->right);
}
void InOrder(TreeNode *T)
{
    if(T==NULL) return;
    InOrder(T->left);
    cout<<T->ch<<" ";
    InOrder(T->right);
}
void PostOrder(TreeNode *T)
{
    if(T==NULL) return;
    PostOrder(T->left);
    PostOrder(T->right);
    cout<<T->ch<<" ";
}
int main(void)
{
    TreeNode *Tree;
    create(Tree);
    cout<<"前序：";
    PreOrder(Tree);cout<<endl;
    cout<<"中序：";
    InOrder(Tree);cout<<endl;
    cout<<"后序：";
    PostOrder(Tree);
    return 0;
}