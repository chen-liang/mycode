//各种版本
#include<iostream>
#include <vector>
#include<algorithm>
#include<ctime>
#include<map>
#include<set>
#include<unordered_map>
using namespace std;
struct CSVDATA {
      int id1, id2,id3;
};
struct CSVDATA1 {
      int id1;
       int id2;
        int t2_id2;
        int t1_id2;
};
struct JOIN {
      int t1_id1,t1_id2, t2_id1,t2_id2;
};
struct RESULT1{
        int max,min,t2_id2,t1_id2;
            bool operator < (const RESULT1 &a) const
    {
        //按id3由小到大排列，如果要由大到小排列，使用“>”号即可
        if(max<a.max) return true ;
        else if(max==a.max&&t2_id2<a.t2_id2) return true;
        else if(max==a.max&&t2_id2==a.t2_id2&&t1_id2<a.t1_id2) return true;
        else return false;      
    }
};
bool compid2(struct CSVDATA & a, struct CSVDATA & b)
{
    return a.id2 < b.id2;
}
bool compid3(struct CSVDATA & a, struct CSVDATA & b)
{
    return a.id3 < b.id3;
}
bool compmax(struct RESULT1 &a, struct RESULT1 &b)
{
    return a.max>b. max;
}
bool compmin(struct RESULT1 &a, struct RESULT1 &b)
{
    return a.min<b. min;
}
bool compt2_id2(struct CSVDATA1 &a, struct CSVDATA1 &b)
{
    return a.t2_id2 < b.t2_id2;
}
//读取csv文件，数据保存在vector<struct CSVDATA>中
vector<CSVDATA> READCSV(char const *file)
{
    vector<CSVDATA> incsv;
    CSVDATA intp;
   FILE *fp;
    fp=fopen(file,"r");
    while(!feof(fp))
    {
        fscanf(fp,"%d,%d,%d",&intp.id1,&intp.id2,&intp.id3);
        incsv.push_back(intp);
        if(feof(fp))
        {
            break;
        }
    }
    fclose(fp);
    return incsv;
}
vector<CSVDATA> READCSV(char const *file)
{
    vector<CSVDATA> incsv;
    CSVDATA intp;
	ifstream inFile(file,ios::in);
	string lineStr;
	while(getline(inFile,lineStr)) //getline来自sstream
	{
		stringstream ss(lineStr);//来自sstream
		string str;
		//按照逗号分隔
		getline(ss,str,',');
		intp.id1=atoi(str.c_str());
        getline(ss,str,',');
		intp.id2=atoi(str.c_str());
        getline(ss,str,',');
		intp.id3=atoi(str.c_str());
		incsv.push_back(intp);//每一行vector数据都放到strArray中去
    }
    return incsv;
}
vector<CSVDATA> fread_analyse(char const *file)
{
    FILE *fp;
    fp=fopen(file,"r");
        fseek(fp,0,SEEK_END); //把指针移动到文件的结尾
        unsigned int len = ftell(fp); //获取文件长度
        rewind(fp); //把指针移动到文件开头 
        char *pbuf=new char[len+1];
        pbuf[len]=0;                    //防止多读一个EOT（4）
        string tm1,tm2,tm3,lineStr;
     fread(pbuf,1,len ,fp);
    cout<<pbuf<<endl;
              vector<CSVDATA> csv1;
              CSVDATA temp;
    stringstream input(pbuf);
    while(getline(input,tm1 , ','))    //将数据以逗号分割写入csvdata中
      {
       if(tm1=="\n") break;
        temp.id1=atoi(tm1.c_str());
        getline(input,tm2 , ',') ;
        temp.id2=atoi(tm2.c_str());
        getline(input,tm3 , '\r') ;
        temp.id3=atoi(tm3.c_str());

        csv1.push_back(temp);
      }
      fclose(fp);
      delete[] pbuf;

      return csv1;
}
//实现JOIN ON
vector<struct JOIN> JOINF(vector<struct CSVDATA>& CSVdata1,vector<struct CSVDATA>& CSVdata2)
{
     vector<struct JOIN> Join;
     struct JOIN join;
    multimap<int,int> mp;
    int len_csv1=CSVdata1.size();
    int len_csv2=CSVdata2.size();
    sort(CSVdata1.begin(),CSVdata1.end(),compid2); 
    for(int i=0;i<len_csv2;i++)
    { 
        mp.insert(make_pair(CSVdata2[i].id3,i));
    }
    for(int i=0;i<len_csv1;i++)
    {
        
            multimap<int,int>::iterator it;
            int n=mp.count(CSVdata1[i].id3);
            if(n==0)
            {
                continue;
            }
            else
            { 
              it=mp.find(CSVdata1[i].id3);
              for(int j=0;j<n;j++)
              {
                  join={CSVdata1[i].id1,CSVdata1[i].id2,CSVdata2[it->second].id1,CSVdata2[it->second].id2};
                Join.push_back(join);
                it++;   
              }
            }
    }
     return Join;
}
vector<struct JOIN> JOINF(vector<struct CSVDATA>& CSVdata1,vector<struct CSVDATA>& CSVdata2)
{
     vector<struct JOIN> Join;
     struct JOIN join;
    unordered_map<int,int> mp;
    int len_csv1=CSVdata1.size();
    int len_csv2=CSVdata2.size();
    sort(CSVdata1.begin(),CSVdata1.end(),compid2); 
    sort(CSVdata2.begin(),CSVdata2.end(),compid3); 
    for(int i=0;i<len_csv2;i++)
    { 
       mp.insert(make_pair(CSVdata2[i].id3,i));
    }
    for(int i=0;i<len_csv1;i++)
    {
        
            unordered_map<int,int>::iterator it;
            it=mp.find(CSVdata1[i].id3);
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
//实现GROUP BY
vector<struct RESULT1>  GROUP(vector<struct JOIN>& JOINYY)
{
    // int len_joinyy=JOINYY.size();

    // sort(JOINYY.begin(),JOINYY.end(),compt1_id2);//先按照t1_id2升序排序
     vector<struct RESULT1>  result;//保存最后的结果
     vector<struct RESULT1> Result;//再分组后的数据
     struct RESULT1 temp1;
     struct RESULT1 temp;
     CSVDATA1 Temp;//
     vector<CSVDATA1> TEMP;//分组后的数据
     int length_joinyy=JOINYY.size();
     int flag1=0;
     int flag2=0;
  for(int i=0;i<length_joinyy;)
 {
        if(flag2==1) flag2=0;
        if(i!=length_joinyy-1)
        {           
            if(JOINYY[i].t1_id2==JOINYY[i+1].t1_id2)
           {  
               Temp={JOINYY[i].t1_id1,JOINYY[i].t2_id1,JOINYY[i].t2_id2,JOINYY[i].t1_id2};
                TEMP.push_back(Temp);
                i++;continue;
           }
        else
        {            
            Temp={JOINYY[i].t1_id1,JOINYY[i].t2_id1,JOINYY[i].t2_id2,JOINYY[i].t1_id2};
                TEMP.push_back(Temp);
                i++;
        }          
    }
    else
    {
        Temp={JOINYY[i].t1_id1,JOINYY[i].t2_id1,JOINYY[i].t2_id2,JOINYY[i].t1_id2};
            TEMP.push_back(Temp);flag1=1;
    }

    int length_TEMP=TEMP.size();
    if(length_TEMP==1)
    {
        temp={Temp.id1,Temp.id2,Temp.t2_id2,Temp.t1_id2};
                 result.push_back(temp);
              vector<struct CSVDATA1>().swap(TEMP);
    }
    else if(length_TEMP>1)
    {
             sort(TEMP.begin(),TEMP.end(),compt2_id2);
        for(int j=0;j<length_TEMP;)
        {
            if(j!=length_TEMP-1)
            {
                if(TEMP[j].t2_id2==TEMP[j+1].t2_id2)
                {
                    temp1={TEMP[j].id1,TEMP[j].id2,TEMP[j].t2_id2,TEMP[j].t1_id2};
                    Result.push_back(temp1);
                    j++;continue;
                }
                else
                {
                    temp1={TEMP[j].id1,TEMP[j].id2,TEMP[j].t2_id2,TEMP[j].t1_id2};
                    Result.push_back(temp1);
                    j++;
                }
            }
            else
            {
                temp1={TEMP[j].id1,TEMP[j].id2,TEMP[j].t2_id2,TEMP[j].t1_id2};
                         Result.push_back(temp1);
                         flag2=1;
            }
            int length_Result=Result.size();
            if(length_Result==1)
            {
                temp={Result[0].max,Result[0].min,Result[0].t2_id2,Result[0].t1_id2};
                     result.push_back(temp);
                     vector<struct RESULT1>().swap(Result);
            }
            else if(length_Result>1)
            {
                        sort(Result.begin(),Result.end(),compmax);
                        temp.max=Result[0].max;temp.t2_id2=Result[0].t2_id2;
                        sort(Result.begin(),Result.end(),compmin);
                        temp.min=Result[0].min;temp.t1_id2=Result[0].t1_id2;
                        result.push_back(temp);
                        vector<struct RESULT1>().swap(Result);
                        TEMP.clear();
            }
            if(flag2==1)  break;
        }
    }
    if(flag1==1)  break;
 }
 return result;
}
//实现GROUP BY
multiset< RESULT1>  GROUP(vector<struct JOIN>& JOINYY)
{
     struct RESULT1 temp;
   multiset<RESULT1> result;
    vector<int> row_res;
    unordered_map<int,int> t1_id2;
    unordered_map<int,int> t2_id2;
    unordered_map<int,int>::iterator t1;
    unordered_map<int,int>::iterator t2;

    int v1_row_len=JOINYY.size();
    for(int i=0;i<v1_row_len;i++)
    {   
        if(t1_id2.count(JOINYY[i].t1_id2)==0)
        {
            row_res.push_back(i);
            t2_id2.clear();
            t1_id2.insert(make_pair(JOINYY[i].t1_id2,i));
            t2_id2.insert(make_pair(JOINYY[i].t2_id2,i));
        }
        else
        {
            if(t2_id2.count(JOINYY[i].t2_id2)==0)
            {
                row_res.push_back(i);
                t2_id2.insert(make_pair(JOINYY[i].t2_id2,i));
               
            }
            else
            {  
                  int group_min,group_min2; 
                  t2=t2_id2.find(JOINYY[i].t2_id2);
                  int j=t2->second;
                  if(JOINYY[i].t1_id2==JOINYY[j].t1_id2 && JOINYY[i].t2_id2==JOINYY[j].t2_id2)
                   { 
                     if (JOINYY[i].t2_id1< JOINYY[j].t2_id1)
                        {
                            group_min=JOINYY[i].t2_id1;
                            group_min2=JOINYY[i].t2_id2;
                        }
                     else
                         {
                            group_min=JOINYY[j].t2_id1;
                            group_min2=JOINYY[j].t2_id2;
                         }
                      if(JOINYY[i].t1_id1>JOINYY[j].t1_id1)
                        {  
                            JOINYY[j].t1_id1=JOINYY[i].t1_id1;  
                        }
                      JOINYY[j].t2_id1=group_min;
                      JOINYY[j].t2_id2=group_min2;    
                    } 
            }
        }
    }
    for(int i=0;i<row_res.size();i++)
    {
        int j=row_res[i];
        temp={JOINYY[j].t1_id1,JOINYY[j].t2_id1,JOINYY[j].t2_id2,JOINYY[j].t1_id2};
        result.insert(temp);
    }
    return result;
}   
//实现ORDER BY
void  ORDERBY(vector<struct RESULT1> &result)
{
    int len_result11=result.size();
    for(int i=0;i<len_result11;i++)
    {
        int temp=i;
        for(int j=i+1;j<len_result11;j++)
        {
            if(result[temp].max>result[j].max)
            {
                temp=j;
            }
            else if(result[temp].max==result[j].max&&result[temp].t2_id2>result[j].t2_id2)
            {
                temp=j;
            }
            else if(result[temp].max==result[j].max&&result[temp].t2_id2==result[j].t2_id2&&result[temp].t1_id2>=result[j].t1_id2)
            {
                temp=j;
            }
        }
        swap(result[i],result[temp]);
    }
}  
void  ORDERBY(vector<struct RESULT1> &result)
{
   //sort(result.begin(),result.end());
     sort(result.begin(),result.end());
}  
int main()
{
vector<struct CSVDATA> csvdata1;
vector<struct CSVDATA> csvdata2;
vector<struct JOIN> JOINNY;    //join 后的结果
multiset<RESULT1> result;
     // 显示读取的数据
    char const *file1="/media/chen/F/C++/mycode/ztedatabase/input3.csv";
    char const *file2="/media/chen/F/C++/mycode/ztedatabase/input4.csv";
    csvdata1=READCSV(file1);
     csvdata2=READCSV(file2);
     JOINNY=JOINF(csvdata1,csvdata2);
	 cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
    vector<struct CSVDATA>().swap(csvdata1);
    vector<struct CSVDATA>().swap(csvdata2);
  result=GROUP(JOINNY);
   vector<struct JOIN>().swap(JOINNY);
   ORDERBY(result);
  for(auto it=result.begin();it!=result.end();it++)
  {
      printf("%d,%d\n",(*it).max,(*it).min);
  }
  result.clear();
   cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
     return 0;    
}
//桶排序
void Bucket_Sort1(vector<CSVDATA1>& A)
{
    int len_csv=A.size();int i=0,j=0;
    vector<CSVDATA1>::iterator p = max_element(A.begin(), A.end(),compid2);
    vector<CSVDATA1>::iterator q = min_element(A.begin(), A.end(),compid2);
    int max=p->id2,min=q->id2;
    int num=max-min+1;
    vector<vector<CSVDATA1>> a(num,vector<CSVDATA1> (0));
    CSVDATA1 temp;
    for(i=0;i<len_csv;i++)
    {
        temp=A[i];int t=temp.id2;
       // if(t!=i) continue;
        a[t-min].push_back(temp);
    }
    int index=0;
    for(i=0;i<num;i++)
    {
        if(a[i].empty()) continue;
        for(j=0;j<a[i].size();j++)
        {
            temp=a[i][j];
            A[index++]=temp;
        }
    }
}
void shellsort1(vector<CSVDATA1>& A,int len_csv)
{
    int i, j, gap;
	for (gap = len_csv / 4; gap > 0; gap /= 4) // 每次的增量，递减趋势
		{
			for (i = gap; i < len_csv; i++) //每次增量下，进行几组插入排序，如第一步就是（从12，9，73，26，37）5次
				for (j = i ; j -gap >= 0 && A[j-gap].id2 > A[j].id2; j -= gap)// 每个元素组中进行直接插入排序，看例子
					swap(A[j-gap], A[j]); 
		}
}