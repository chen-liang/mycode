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
/*
TreeNode *create()
{
	char ch[20];
	int i = 0, flag = 0 ,top = 0;
	YTreeNode *tree, *head, *stack[20], *st;
	
	std::cin>>ch;
	tree = (struct node *)malloc(sizeof(struct node));
	head=tree;
	tree->data = ch[i];
	tree->lchild = NULL;
	tree->rchild = NULL;
    stack[top++] = tree;
    int a = 0;
	i++;
	while(i<strlen(ch))
	{
		if((ch[i]=='#') && (flag==1))
		{
			st=stack[--top];
			while(stack[top-1]->rchild == st)
			{
				st=stack[--top];
			}
		}
		else if((ch[i]=='#') && (flag==0))
		{
			flag = 1;
		}
		else if(ch[i]!='#')
		{
			tree = new TreeNode;
			tree->data = ch[i];
			tree->lchild = NULL;
			tree->rchild = NULL;
			if(flag == 0)
			{
				stack[top-1]->lchild = tree;
				stack[top] = tree;
				top++;
			}
			if(flag == 1)
			{
				flag = 0;
				stack[top-1]->rchild = tree;
				top++;
			}
		}
		else
		{
			std::cout<<"sorry,your enter is error"<<std::endl;
			exit(0);
		}
		i++;
	}
	return head;
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