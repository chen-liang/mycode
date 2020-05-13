#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

typedef struct data
{
    int number;
    string name;
    string sex;
}data1;

typedef struct listpoint
{
    data1 *information;
    listpoint *next;
    listpoint *last;
    listpoint *branch;
}listpoint;
/********************************************************/
listpoint *create_normal_list(int n)
{
    listpoint *head,*normal,*end;
    head=(listpoint*)malloc(sizeof(listpoint));
    head->information=(data1*)malloc(sizeof(data1));
    end=head;
    for(int i=0;i<n;i++)
    {
        normal=(listpoint*)malloc(sizeof(listpoint));
        normal->information=(data1*)malloc(sizeof(data1));
        cout<<"input the number :";
        cin>>normal->information->number;
        cout<<"input the name   :";
        cin>>normal->information->name;
        cout<<"input the sex    :";
        cin>>normal->information->sex;
        cout<<"----------------------------------"<<endl;
        end->next=normal;
        normal->last=end;
        end=normal;
    }
    end->next=NULL;
    head->last=NULL;
    return head;
}
listpoint *create_loop_list(int n)
{
    listpoint *head,*normal,*end;
    head=(listpoint*)malloc(sizeof(listpoint));
    head->information=(data1*)malloc(sizeof(data1));
    end=head;
    for(int i=0;i<n;i++)
    {
        normal=(listpoint*)malloc(sizeof(listpoint));
        normal->information=(data1*)malloc(sizeof(data1));
        cout<<"input the number :";
        cin>>normal->information->number;
        cout<<"input the name   :";
        cin>>normal->information->name;
        cout<<"input the sex    :";
        cin>>normal->information->sex;
        cout<<"----------------------------------"<<endl;
        end->next=normal;
        normal->last=end;
        end=normal;
    }
    end->next=head;
    head->last=end;
    return head;
}
listpoint *create_random_branch_list(int n)
{
    listpoint *search_point(listpoint *list,int n);
    listpoint *head;
    head=create_normal_list(n);
    listpoint *p,*bp;
    p=head;
    srand((int)(time(NULL)));
    int randnum;
    while((p=p->next)!=NULL)
    {
        randnum=rand()%n+1;
        bp=search_point(head,randnum);
        p->branch=bp;
    }
    return head;
}
listpoint *create_random_sort_list(int n)
{
    listpoint *head;
    head=create_normal_list(n);
    listpoint *p1,*p2;
    int n1=0;
    int n2=n;
    srand((int)(time(NULL)));
    int randnum;
    while(n2!=1)
    { 
        p1=head;
        p2=head;
        randnum=rand()%n2+1+n1;
        for(int i=0;i<randnum;i++)
        {p2=p2->next;}
        for(int i=0;i<n1;i++)
        {p1=p1->next;}
        if(randnum==n)
        {
            p2->last->next=NULL;
        }
        else
        {
            p2->next->last=p2->last;
            p2->last->next=p2->next;
        }
        p1->next->last=p2;
        p2->next=p1->next;
        p1->next=p2;
        p2->last=p1;
        n1+=1;
        n2-=1;
    
    }
    return head;
}
/********************************************************/
void change_point(listpoint *list,int n,data1 *ifmation)
{
    listpoint *p;
    p=list;
    for(int i=0;i<n;i++)
    {
        p=p->next;
    }
    p->information=ifmation;
}
void delete_point(listpoint *list,int n)
{
    listpoint *p;
    p=list;
    for(int i=0;i<n;i++)
    {
        p=p->next;
    }
    p->last->next=p->next;
    p->next->last=p->last;
    free(p);
}
void insert_point(listpoint *list,int n,data1 *ifmation)
{
    listpoint *p;
    p=list;
    for(int i=0;i<n-1;i++)
    {
        p=p->next;
    }
    listpoint *insertpoint;
    insertpoint=(listpoint*)malloc(sizeof(listpoint));
    insertpoint->information=ifmation;
    insertpoint->next=p->next;
    p->next->last=insertpoint;
    p->next=insertpoint;
    insertpoint->last=p;
}
listpoint *search_point(listpoint *list,int n)
{
    listpoint *p;
    p=list;
    for(int i=0;i<n;i++)
    {
        p=p->next;
    }
    return p;
}
void output_point(listpoint *point)
{
    cout<<"the number is :"<<point->information->number<<endl;
    cout<<"the name   is :"<<point->information->name<<endl;
    cout<<"the sex    is :"<<point->information->sex<<endl;
    cout<<"----------------------------------"<<endl;
}
void output_list(listpoint *point)
{
    listpoint *p;
    p=point;
    cout<<endl<<endl<<endl;
    while((p=p->next)!=NULL)
    {
        output_point(p);
    }
}
void output_list_part(listpoint *list,int m,int n)
{
    int difference=n-m;
    listpoint *p;
    p=list;
    cout<<endl<<endl<<endl;
    for(int i=0;i<m;i++)
    {
        p=p->next; 
    }
    for(int i=0;i<difference+1;i++)
    {
        output_point(p);
        p=p->next;
    }
}
/***************************************************************/
int main()
{
    listpoint *head;
    head=create_random_sort_list(7);
    output_list(head);
    system("pause");
    return 0;
}

