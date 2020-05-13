//����ʵ�ְ�/home/web/ztedatabase/input1.csv
#include<iostream>
#include <vector>
//#include<ctime>
#include<fstream>
#include<sstream>
#include<unordered_map>
using namespace std;
struct CSVDATA1 {                                                           //�洢t1�������
      int id1, id2,id3;
     bool operator < (const CSVDATA1 &a) const   //����<������t1_id2��С��������
    {
        return id2 < a.id2;
    }
};
struct CSVDATA2 {                                                             //�洢t2�������
      int id1, id2,id3;
       bool operator < (const CSVDATA2 &a) const //����<������t2_id3��С��������
    {
     return id3 < a.id3;
    }
};
struct JOIN {                                                                      //�洢join�������
      int t1_id1,t1_id2, t2_id1,t2_id2;
};
struct RESULT{                                                               //�洢group by��Ľ��
        int max,min,t2_id2,t1_id2;
        bool operator < (const RESULT &a) const
    {
        //��max(t1_id1),t2_id2,t1_id2��С�������У����Ҫ�ɴ�С���У�ʹ�á�>���ż���
        if(max<a.max) return true ;
        else if(max==a.max&&t2_id2<a.t2_id2) return true;
        else if(max==a.max&&t2_id2==a.t2_id2&&t1_id2<a.t1_id2) return true;
        else return false;      
    }
};

vector<CSVDATA1> READCSV1(char const *file);           //�����ݴ�input1�ж�ȡ��CSVDATA1��
vector<CSVDATA2> READCSV2(char const *file);          //�����ݴ�input2�ж�ȡ��CSVDATA2��
void quicksort1(vector<CSVDATA1>&A,int,int);            //t1�����ݰ���id2��������
void quicksort2(vector<CSVDATA2>& A,int,int);           //t2�����ݰ���id3��������
vector<struct JOIN> JOINF(vector<CSVDATA1>& ,vector<CSVDATA2>& );//ʵ��join on
vector< RESULT>  GROUP(vector<struct JOIN>& JOINYY);        //ʵ��group by  
void  ORDERBY(vector<struct RESULT> &A,int l,int r);                 //ʵ��order by

int main()
{
    //ios::sync_with_stdio(false);//C++�������������iostream)������C�����������stdio��
    //cin.tie(0);//��������������
    vector<struct CSVDATA1> csvdata1;   //�洢t1
    vector<struct CSVDATA2> csvdata2;   //�洢t2
    vector<struct JOIN> JOINNY;    //�洢join ��Ľ��
    vector<RESULT> result;    //�洢group by��Ľ��
    char const *file1="/media/chen/F/C++/mycode/ztedatabase/input7.csv";
    char const *file2="/media/chen/F/C++/mycode/ztedatabase/input8.csv";
    csvdata1=READCSV1(file1);//��ȡ����
    csvdata2=READCSV2(file2);
    JOINNY=JOINF(csvdata1,csvdata2);//ʵ��join on t1.id3=t2.id3
    vector<struct CSVDATA1>().swap(csvdata1);
    vector<struct CSVDATA2>().swap(csvdata2);
    result=GROUP(JOINNY);//ʵ��group by+select  max(t1.id1),min(t2.id1)
   vector<struct JOIN>().swap(JOINNY);
   int r=result.size()-1;
   ORDERBY(result,0,r);  //ʵ��order by max(t1.id1),t2.id2,t1.id2
    for(auto it=result.begin();it!=result.end();it++)
    {
        printf("%d,%d\n",(*it).max,(*it).min);
    }
  vector<RESULT>().swap(result);
     return 0;    
}

/*
* �������ܣ���ȡCSV�ļ����������е����ݣ�Ȼ��洢�������С�
* ����������
*     char const *file- ����ȡ��CSV�ļ�·����
* ����ֵ��vector<CSVDATA1>  �洢�������CSV����
*/
vector<CSVDATA1> READCSV1(char const *file)
{
   FILE *fp;
    fp=fopen(file,"r");
    fseek(fp,0,SEEK_END); //��ָ���ƶ����ļ��Ľ�β
    unsigned int len = ftell(fp); //��ȡ�ļ�����
    rewind(fp); //��ָ���ƶ����ļ���ͷ 
    char *pbuf=new char[len+1];
    pbuf[len]=0;
    string tm1,tm2,tm3;
    fread(pbuf,1,len ,fp);    //�����ݶ����ַ���pbuf
    vector<CSVDATA1> csv1;
    CSVDATA1 temp;
    stringstream input(pbuf);
    while(getline(input,tm1 , ','))    //�������Զ��ŷָ�д��csvdata��
      {
       if(tm1=="\n") break;                //�жϽ�β�Ƿ��п���
        temp.id1=atoi(tm1.c_str());
        getline(input,tm2 , ',') ;
        temp.id2=atoi(tm2.c_str());
        getline(input,tm3 , '\r') ;
        temp.id3=atoi(tm3.c_str());
        csv1.push_back(temp);
      }
      delete[] pbuf;
      fclose(fp);
      return csv1;
}
/*
* �������ܣ���ȡCSV�ļ����������е����ݣ�Ȼ��洢�������С�
* ����������
*     char const *file- ����ȡ��CSV�ļ�·����
* ����ֵ��vector<CSVDATA2>  �洢�������CSV����
*/
vector<CSVDATA2> READCSV2(char const *file)
{
    FILE *fp;
    fp=fopen(file,"r");
    fseek(fp,0,SEEK_END); //��ָ���ƶ����ļ��Ľ�β
    unsigned int len = ftell(fp); //��ȡ�ļ�����
    rewind(fp); //��ָ���ƶ����ļ���ͷ 
    char *pbuf=new char[len+1];
    pbuf[len]=0;
    string tm1,tm2,tm3;
    fread(pbuf,1,len ,fp);    //�����ݶ����ַ���pbuf
    vector<CSVDATA2> csv1;
    CSVDATA2 temp;
    stringstream input(pbuf);
    while(getline(input,tm1 , ','))    //�������Զ��ŷָ�д��csvdata��
      {
        if(tm1=="\n") break;               //�жϽ�β�Ƿ��п���
        temp.id1=atoi(tm1.c_str());
        getline(input,tm2 , ',') ;
        temp.id2=atoi(tm2.c_str());
        getline(input,tm3 , '\r') ;
        temp.id3=atoi(tm3.c_str());
        csv1.push_back(temp);
      }
      delete[] pbuf;
      fclose(fp);
      return csv1;
}

/*
* �������ܣ�ʵ��join on t1.id3=t2.id3
* ����������
*     vector<struct CSVDATA1>& CSVdata1 t1������ݣ�
*     vector<struct CSVDATA2>& CSVdata2 t2������ݣ�
* ����ֵ��vector<struct JOIN>  �洢join�������
*/
vector<struct JOIN> JOINF(vector<struct CSVDATA1>& CSVdata1,vector<struct CSVDATA2>& CSVdata2)
{
     vector<struct JOIN> Join;
     struct JOIN join;
    unordered_map<int,int> mp;              //�洢����������t2.id3���к�
    int len_csv1=CSVdata1.size();
    int len_csv2=CSVdata2.size();
    quicksort1(CSVdata1,0,len_csv1-1);   //t1����id2��������
    quicksort2(CSVdata2,0,len_csv2-1);   //t2����id3��������
    for(int i=0;i<len_csv2;i++)                         //������������t2.id3���кŴ洢�ڹ�ϣ����
    { 
       mp.insert(make_pair(CSVdata2[i].id3,i));
    }
    for(int i=0;i<len_csv1;i++)                        //����t1.id3����t1.id3=t2.id3ʱ��join t1,t2��
    {
            unordered_map<int,int>::iterator it;
            it=mp.find(CSVdata1[i].id3);        //��t2.id3��Ѱ��t1.id3
            if(it!=mp.end())
            {
                int j=it->second;
                while(CSVdata1[i].id3==CSVdata2[j].id3)
                {
                    join={CSVdata1[i].id1,CSVdata1[i].id2,CSVdata2[j].id1,CSVdata2[j].id2};
                    Join.push_back(join);
                        j++; 
                        if(j==len_csv2) break;
                }
            }
    }
     return Join;
}

/*
* �������ܣ�ʵ��group by+select  max(t1.id1),min(t2.id1)
* ����������
*     vector<struct JOIN>& JOINYY   join on������ݣ�
* ����ֵ��vector< RESULT>  GROUP  �洢group by�������
*/
vector< RESULT>  GROUP(vector<struct JOIN>& JOINYY)
{
     struct RESULT temp;
    vector<int> res_row;                                 //�洢���ս����join�е��к�
    unordered_map<int,int> t1_id2;          //�洢t1.id2���к�
    unordered_map<int,int> t2_id2;          //�洢t2.id2���к�
    unordered_map<int,int>::iterator t1; 
    unordered_map<int,int>::iterator t2;
    int len_joinyy=JOINYY.size();    

    for(int i=0;i<len_joinyy;i++)                //����join���t1.id2��t2.id2
    {   
        if(t1_id2.find(JOINYY[i].t1_id2)==t1_id2.end())//����t1.id2����
        {
            res_row.push_back(i);
            t2_id2.clear();
            t1_id2.insert(make_pair(JOINYY[i].t1_id2,i));
            t2_id2.insert(make_pair(JOINYY[i].t2_id2,i));
        }
        else
        {
            if(t2_id2.find(JOINYY[i].t2_id2)==t2_id2.end()) //t1.id2��ͬʱ����t2.id2����
            {
                res_row.push_back(i);                                             //�洢ÿһ����к�
                t2_id2.insert(make_pair(JOINYY[i].t2_id2,i)); 
            }
            else
            {  
                  t2=t2_id2.find(JOINYY[i].t2_id2);
                  int j=t2->second;
                  //select  max(t1.id1),min(t2.id1)����res_row��ÿһ�е�t1.id2,t2.id2��Ϊ���
                  if(JOINYY[i].t1_id2==JOINYY[j].t1_id2 && JOINYY[i].t2_id2==JOINYY[j].t2_id2)  
                   { 
                       JOINYY[j].t2_id1=JOINYY[i].t2_id1<JOINYY[j].t2_id1?JOINYY[i].t2_id1:JOINYY[j].t2_id1;
                       JOINYY[j].t1_id1=JOINYY[i].t1_id1>JOINYY[j].t1_id1?JOINYY[i].t1_id1:JOINYY[j].t1_id1;
                    } 
            }
        }
    }

    vector<RESULT> result(res_row.size());
    for(int i=0;i<res_row.size();i++)           //����res_row,������洢��result��
    {
        int j=res_row[i];
        temp={JOINYY[j].t1_id1,JOINYY[j].t2_id1,JOINYY[j].t2_id2,JOINYY[j].t1_id2};
        result[i]=temp;
    }
    return result;
} 

/*
* �������ܣ�ʵ��order by+select  max(t1.id1),t2.id2,t1.id2
* ����������
*     vector<struct RESULT> &A  group by�������
*      int l ,int r  l,r�ֱ�Ϊresult�����ұ߽磬l=0;r=result.size()-1
* ����ֵ����
*/
//ʵ��ORDER BY
void  ORDERBY(vector<struct RESULT> &A,int l,int r)
{
    if(l<r)
    {
        int i=l,j=r;
        RESULT temp=A[l];              //��һ����Ϊ��׼ֵ��ʵ�ֿ�������
        while(i<j)
        {
            while(i<j&&temp<A[j])// ���������ҵ�һ��С��temp����
            { 
                j--;
            }
            if(i<j) 
            { 
                A[i++]=A[j];
            }
            while(i<j&&A[i]<temp)// ���������ҵ�һ�����ڵ���temp����
             {
                 i++;
             }
             if(i<j) 
             {
                 A[j--]=A[i];
             }
        }
    A[i]=temp;
    ORDERBY( A,l,i-1);
    ORDERBY( A,i+1,r);
    }
}

/*
* �������ܣ�ʵ��order by  t1.id2��������
* ����������
*     vector<CSVDATA1> &A, t1�������
*      int l ,int r  l,r�ֱ�ΪA�����ұ߽磬l=0;r=A.size()-1
* ����ֵ����
*/
void quicksort1(vector<CSVDATA1> &A,int l,int r)
{ 
    if(l<r)
    {
        int i=l,j=r;
        CSVDATA1 temp=A[l];                 //��һ����Ϊ��׼ֵ��ʵ�ֿ�������
        while(i<j)
        {
                 while(i<j&&temp<A[j])// ���������ҵ�һ��С��temp����
            { 
                j--;
            }
             if(i<j) 
             {
                 A[i++]=A[j];
             }
              while(i<j&&A[i]<temp)// ���������ҵ�һ�����ڵ���temp����
            {
                i++;
            }
                if(i<j)
                {
                     A[j--]=A[i];
                }
        }
    A[i]=temp;
    quicksort1(A,l,i-1);//�ݹ����
    quicksort1(A,i+1,r);
    }
}

/*
* �������ܣ�ʵ��order by  t2.id3��������
* ����������
*     vector<CSVDATA2> &A, t2�������
*      int l ,int r  l,r�ֱ�ΪA�����ұ߽磬l=0;r=A.size()-1
* ����ֵ����
*/
void quicksort2(vector<CSVDATA2>& A,int l,int r)
{ 
    if(l<r)
    {
        int i=l,j=r;
        CSVDATA2 temp=A[l];             //��һ����Ϊ��׼ֵ��ʵ�ֿ�������
        while(i<j)
        {
            while(i<j&&temp<A[j])// ���������ҵ�һ��С��temp����
            { 
                j--;
            }
            if(i<j) 
            { 
                A[i++]=A[j];
            }
            while(i<j&&A[i]<temp)// ���������ҵ�һ�����ڵ���temp����
             {
                 i++;
             }
             if(i<j) 
             {
                 A[j--]=A[i];
             }
        }
    A[i]=temp;
    quicksort2( A,l,i-1);//�ݹ����
    quicksort2( A,i+1,r);
    }
}