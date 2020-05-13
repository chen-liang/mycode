//功能实现版/home/web/ztedatabase/input1.csv
#include<iostream>
#include <vector>
//#include<ctime>
#include<fstream>
#include<sstream>
#include<unordered_map>
using namespace std;
struct CSVDATA1 {                                                           //存储t1表的数据
      int id1, id2,id3;
     bool operator < (const CSVDATA1 &a) const   //重载<，按照t1_id2从小到大排列
    {
        return id2 < a.id2;
    }
};
struct CSVDATA2 {                                                             //存储t2表的数据
      int id1, id2,id3;
       bool operator < (const CSVDATA2 &a) const //重载<，按照t2_id3从小到大排列
    {
     return id3 < a.id3;
    }
};
struct JOIN {                                                                      //存储join后的数据
      int t1_id1,t1_id2, t2_id1,t2_id2;
};
struct RESULT{                                                               //存储group by后的结果
        int max,min,t2_id2,t1_id2;
        bool operator < (const RESULT &a) const
    {
        //按max(t1_id1),t2_id2,t1_id2由小到大排列，如果要由大到小排列，使用“>”号即可
        if(max<a.max) return true ;
        else if(max==a.max&&t2_id2<a.t2_id2) return true;
        else if(max==a.max&&t2_id2==a.t2_id2&&t1_id2<a.t1_id2) return true;
        else return false;      
    }
};

vector<CSVDATA1> READCSV1(char const *file);           //将数据从input1中读取到CSVDATA1中
vector<CSVDATA2> READCSV2(char const *file);          //将数据从input2中读取到CSVDATA2中
void quicksort1(vector<CSVDATA1>&A,int,int);            //t1表数据按照id2降序排序
void quicksort2(vector<CSVDATA2>& A,int,int);           //t2表数据按照id3降序排序
vector<struct JOIN> JOINF(vector<CSVDATA1>& ,vector<CSVDATA2>& );//实现join on
vector< RESULT>  GROUP(vector<struct JOIN>& JOINYY);        //实现group by  
void  ORDERBY(vector<struct RESULT> &A,int l,int r);                 //实现order by

int main()
{
    //ios::sync_with_stdio(false);//C++的输入输出流（iostream)不兼容C的输入输出（stdio）
    //cin.tie(0);//解除输入输出流绑定
    vector<struct CSVDATA1> csvdata1;   //存储t1
    vector<struct CSVDATA2> csvdata2;   //存储t2
    vector<struct JOIN> JOINNY;    //存储join 后的结果
    vector<RESULT> result;    //存储group by后的结果
    char const *file1="/media/chen/F/C++/mycode/ztedatabase/input7.csv";
    char const *file2="/media/chen/F/C++/mycode/ztedatabase/input8.csv";
    csvdata1=READCSV1(file1);//读取数据
    csvdata2=READCSV2(file2);
    JOINNY=JOINF(csvdata1,csvdata2);//实现join on t1.id3=t2.id3
    vector<struct CSVDATA1>().swap(csvdata1);
    vector<struct CSVDATA2>().swap(csvdata2);
    result=GROUP(JOINNY);//实现group by+select  max(t1.id1),min(t2.id1)
   vector<struct JOIN>().swap(JOINNY);
   int r=result.size()-1;
   ORDERBY(result,0,r);  //实现order by max(t1.id1),t2.id2,t1.id2
    for(auto it=result.begin();it!=result.end();it++)
    {
        printf("%d,%d\n",(*it).max,(*it).min);
    }
  vector<RESULT>().swap(result);
     return 0;    
}

/*
* 函数功能：读取CSV文件，分析其中的内容，然后存储在容器中。
* 参数描述：
*     char const *file- 待读取的CSV文件路径；
* 返回值：vector<CSVDATA1>  存储分析后的CSV内容
*/
vector<CSVDATA1> READCSV1(char const *file)
{
   FILE *fp;
    fp=fopen(file,"r");
    fseek(fp,0,SEEK_END); //把指针移动到文件的结尾
    unsigned int len = ftell(fp); //获取文件长度
    rewind(fp); //把指针移动到文件开头 
    char *pbuf=new char[len+1];
    pbuf[len]=0;
    string tm1,tm2,tm3;
    fread(pbuf,1,len ,fp);    //将数据读入字符串pbuf
    vector<CSVDATA1> csv1;
    CSVDATA1 temp;
    stringstream input(pbuf);
    while(getline(input,tm1 , ','))    //将数据以逗号分割写入csvdata中
      {
       if(tm1=="\n") break;                //判断结尾是否有空行
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
* 函数功能：读取CSV文件，分析其中的内容，然后存储在容器中。
* 参数描述：
*     char const *file- 待读取的CSV文件路径；
* 返回值：vector<CSVDATA2>  存储分析后的CSV内容
*/
vector<CSVDATA2> READCSV2(char const *file)
{
    FILE *fp;
    fp=fopen(file,"r");
    fseek(fp,0,SEEK_END); //把指针移动到文件的结尾
    unsigned int len = ftell(fp); //获取文件长度
    rewind(fp); //把指针移动到文件开头 
    char *pbuf=new char[len+1];
    pbuf[len]=0;
    string tm1,tm2,tm3;
    fread(pbuf,1,len ,fp);    //将数据读入字符串pbuf
    vector<CSVDATA2> csv1;
    CSVDATA2 temp;
    stringstream input(pbuf);
    while(getline(input,tm1 , ','))    //将数据以逗号分割写入csvdata中
      {
        if(tm1=="\n") break;               //判断结尾是否有空行
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
* 函数功能：实现join on t1.id3=t2.id3
* 参数描述：
*     vector<struct CSVDATA1>& CSVdata1 t1表的数据；
*     vector<struct CSVDATA2>& CSVdata2 t2表的数据；
* 返回值：vector<struct JOIN>  存储join后的数据
*/
vector<struct JOIN> JOINF(vector<struct CSVDATA1>& CSVdata1,vector<struct CSVDATA2>& CSVdata2)
{
     vector<struct JOIN> Join;
     struct JOIN join;
    unordered_map<int,int> mp;              //存储升序排序后的t2.id3与行号
    int len_csv1=CSVdata1.size();
    int len_csv2=CSVdata2.size();
    quicksort1(CSVdata1,0,len_csv1-1);   //t1表按照id2升序排序
    quicksort2(CSVdata2,0,len_csv2-1);   //t2表按照id3升序排序
    for(int i=0;i<len_csv2;i++)                         //将升序排序后的t2.id3与行号存储在哈希表中
    { 
       mp.insert(make_pair(CSVdata2[i].id3,i));
    }
    for(int i=0;i<len_csv1;i++)                        //遍历t1.id3，当t1.id3=t2.id3时，join t1,t2；
    {
            unordered_map<int,int>::iterator it;
            it=mp.find(CSVdata1[i].id3);        //在t2.id3中寻找t1.id3
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
* 函数功能：实现group by+select  max(t1.id1),min(t2.id1)
* 参数描述：
*     vector<struct JOIN>& JOINYY   join on后的数据；
* 返回值：vector< RESULT>  GROUP  存储group by后的数据
*/
vector< RESULT>  GROUP(vector<struct JOIN>& JOINYY)
{
     struct RESULT temp;
    vector<int> res_row;                                 //存储最终结果在join中的行号
    unordered_map<int,int> t1_id2;          //存储t1.id2与行号
    unordered_map<int,int> t2_id2;          //存储t2.id2与行号
    unordered_map<int,int>::iterator t1; 
    unordered_map<int,int>::iterator t2;
    int len_joinyy=JOINYY.size();    

    for(int i=0;i<len_joinyy;i++)                //遍历join后的t1.id2与t2.id2
    {   
        if(t1_id2.find(JOINYY[i].t1_id2)==t1_id2.end())//按照t1.id2分组
        {
            res_row.push_back(i);
            t2_id2.clear();
            t1_id2.insert(make_pair(JOINYY[i].t1_id2,i));
            t2_id2.insert(make_pair(JOINYY[i].t2_id2,i));
        }
        else
        {
            if(t2_id2.find(JOINYY[i].t2_id2)==t2_id2.end()) //t1.id2相同时按照t2.id2分组
            {
                res_row.push_back(i);                                             //存储每一组的行号
                t2_id2.insert(make_pair(JOINYY[i].t2_id2,i)); 
            }
            else
            {  
                  t2=t2_id2.find(JOINYY[i].t2_id2);
                  int j=t2->second;
                  //select  max(t1.id1),min(t2.id1)，将res_row中每一行的t1.id2,t2.id2置为最大
                  if(JOINYY[i].t1_id2==JOINYY[j].t1_id2 && JOINYY[i].t2_id2==JOINYY[j].t2_id2)  
                   { 
                       JOINYY[j].t2_id1=JOINYY[i].t2_id1<JOINYY[j].t2_id1?JOINYY[i].t2_id1:JOINYY[j].t2_id1;
                       JOINYY[j].t1_id1=JOINYY[i].t1_id1>JOINYY[j].t1_id1?JOINYY[i].t1_id1:JOINYY[j].t1_id1;
                    } 
            }
        }
    }

    vector<RESULT> result(res_row.size());
    for(int i=0;i<res_row.size();i++)           //遍历res_row,将结果存储到result中
    {
        int j=res_row[i];
        temp={JOINYY[j].t1_id1,JOINYY[j].t2_id1,JOINYY[j].t2_id2,JOINYY[j].t1_id2};
        result[i]=temp;
    }
    return result;
} 

/*
* 函数功能：实现order by+select  max(t1.id1),t2.id2,t1.id2
* 参数描述：
*     vector<struct RESULT> &A  group by后的数据
*      int l ,int r  l,r分别为result的左右边界，l=0;r=result.size()-1
* 返回值：无
*/
//实现ORDER BY
void  ORDERBY(vector<struct RESULT> &A,int l,int r)
{
    if(l<r)
    {
        int i=l,j=r;
        RESULT temp=A[l];              //第一个数为基准值，实现快速排序
        while(i<j)
        {
            while(i<j&&temp<A[j])// 从右向左找第一个小于temp的数
            { 
                j--;
            }
            if(i<j) 
            { 
                A[i++]=A[j];
            }
            while(i<j&&A[i]<temp)// 从左向右找第一个大于等于temp的数
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
* 函数功能：实现order by  t1.id2快速排序
* 参数描述：
*     vector<CSVDATA1> &A, t1表的数据
*      int l ,int r  l,r分别为A的左右边界，l=0;r=A.size()-1
* 返回值：无
*/
void quicksort1(vector<CSVDATA1> &A,int l,int r)
{ 
    if(l<r)
    {
        int i=l,j=r;
        CSVDATA1 temp=A[l];                 //第一个数为基准值，实现快速排序
        while(i<j)
        {
                 while(i<j&&temp<A[j])// 从右向左找第一个小于temp的数
            { 
                j--;
            }
             if(i<j) 
             {
                 A[i++]=A[j];
             }
              while(i<j&&A[i]<temp)// 从左向右找第一个大于等于temp的数
            {
                i++;
            }
                if(i<j)
                {
                     A[j--]=A[i];
                }
        }
    A[i]=temp;
    quicksort1(A,l,i-1);//递归调用
    quicksort1(A,i+1,r);
    }
}

/*
* 函数功能：实现order by  t2.id3快速排序
* 参数描述：
*     vector<CSVDATA2> &A, t2表的数据
*      int l ,int r  l,r分别为A的左右边界，l=0;r=A.size()-1
* 返回值：无
*/
void quicksort2(vector<CSVDATA2>& A,int l,int r)
{ 
    if(l<r)
    {
        int i=l,j=r;
        CSVDATA2 temp=A[l];             //第一个数为基准值，实现快速排序
        while(i<j)
        {
            while(i<j&&temp<A[j])// 从右向左找第一个小于temp的数
            { 
                j--;
            }
            if(i<j) 
            { 
                A[i++]=A[j];
            }
            while(i<j&&A[i]<temp)// 从左向右找第一个大于等于temp的数
             {
                 i++;
             }
             if(i<j) 
             {
                 A[j--]=A[i];
             }
        }
    A[i]=temp;
    quicksort2( A,l,i-1);//递归调用
    quicksort2( A,i+1,r);
    }
}