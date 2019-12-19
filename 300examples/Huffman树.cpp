#include<iostream>
#include<string>
using namespace std;

struct huffTree
{
    int parent;
    int lchild;
    int rchild;
    int weight;
    string flag;
};
struct Lowest_Node
{
    char ch;
    int ch_num;
};
void coding(int length,huffTree tree[],int n,int &a,int &b)
{
    int i;
    int r,s;
    r=s=length;
    for(i=0;i<n;i++)
    {
        if((tree[i].weight<r)&&(tree[i].parent==-1))
        {
            r=tree[i].weight;
            a=i;
        }
    }
    for(i=0;i<n;i++)
    {
        if((tree[i].weight<s)&&(i!=a)&&(tree[i].parent==-1))
        {
            s=tree[i].weight;
            b=i;
        }
    }
}
void frequency(string str)
{
    int length=str.length();
    Lowest_Node *node=new Lowest_Node[length];
    int i,j;
    for(i=0;i<length;i++)
    {
        node[i].ch_num=0;
    }
    int char_type_num=0;
    for(i=0;i<length;i++)
    {
        for(j=0;j<char_type_num;j++)
        {
            if(str[i]==node[j].ch||(node[j].ch>='a'&&node[j].ch<='z'&&str[i]+32==node[j].ch))
                break;
            
        }
        if(j<char_type_num)
            node[j].ch_num++;
        else
        {
            if(str[i]>='A'&&str[i]<='Z')
                node[j].ch=str[i]+32;
            else
                node[j].ch=str[i];
            node[j].ch_num++;
            char_type_num++;
            
        }
        
    }
    for(i=0;i<char_type_num;i++)
    {
        for(j=i;j<char_type_num;j++)
        {
            if(node[j].ch_num<node[j+1].ch_num)
            {
                int temp;
                char ch_temp;
                temp=node[j].ch_num;
                ch_temp=node[j].ch;
                node[j].ch_num=node[j+1].ch_num;
                node[j].ch=node[j+1].ch;
                node[j+1].ch_num=temp;
                node[j+1].ch=ch_temp;
            }
        }
    }
    for(i=0;i<char_type_num;i++)
        cout<<"字符"<<node[i].ch<<"出现了"<<node[i].ch_num<<"次"<<endl;
    huffTree *huff=new huffTree[2*char_type_num-1];
    huffTree temp;
    string *code=new string[2*char_type_num-1];
    for(i=0;i<2*char_type_num-1;i++)
    {
        huff[i].lchild=-1;
        huff[i].parent=-1;
        huff[i].rchild=-1;
        huff[i].flag=-1;
    }
    for(j=0;j<char_type_num;j++)
    {
        huff[j].weight=node[j].ch_num;
    }
    int min1,min2;
    for(int k=char_type_num;k<2*char_type_num-1;k++)
    {
        coding(length,huff,k,min1,min2);
        huff[min1].parent=k;
        huff[min2].parent=k;
        huff[min1].flag='0';
        huff[min2].flag='1';
        huff[k].lchild=min1;
        huff[k].rchild=min2;
        huff[k].weight=huff[min1].weight+huff[min2].weight;

    }
    for(i=0;i<char_type_num;i++)
    {
        temp=huff[i];
        while(1)
        {
            code[i]=temp.flag+code[i];
            temp=huff[temp.parent];
            if(temp.parent==-1)
                break;
        }
    }
    cout<<"字符串的每个字符Huffman编码为："<<endl;
    for(i=0;i<char_type_num;i++)
        cout<<node[i].ch<<" "<<code[i]<<endl;
    cout<<"整个字符串的Huffman编码为："<<endl;
    for(i=0;i<length;i++)
    {
        for(j=0;j<char_type_num;j++)
        {
            if(str[i]==node[j].ch)
                cout<<code[j];
        }
    }
    delete[] node;
    node=NULL;
    delete[] huff;
    huff=NULL;
    delete[] code;
    code=NULL;
}
int main()
{
    int length =0;
    string str;
    cout<<"请输入一个字符串：";
    cin>>str;
    frequency(str);
    return 0;
}

