#include<stdlib.h>
#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<map>
#include<ctime>
using namespace std;

//实现的是t1 join t2 on t1.id3=t2.id3
vector<int> join_on(vector<vector<int>> v1,vector<vector<int>> v2)
{
    vector<int> res;

    multimap<int,int> mp;

    int v1_row_len=v1.size();
    int v2_row_len=v2.size();
    //将v1.id3中的元素保存在红黑树中

    for(int i=0;i<v1_row_len;i++)
    { 
        mp.insert(make_pair(v1[i][2],i));
    }
    for(int i=0;i<v2_row_len;i++)
    {
        
            multimap<int,int>::iterator it;
            int n=mp.count(v2[i][2]);
            if(n==0)
            {
                continue;
            }
            else
            { 
              it=mp.find(v2[i][2]);
              for(int j=0;j<n;j++)
              {
                res.insert(res.end(),v1[it->second].begin(),v1[it->second].begin()+2);
                res.insert(res.end(),v2[i].begin(),v2[i].begin()+2);
                it++;   
              }
            }
    }
    return res;
    }
//数组的赋值
vector<int> assign(vector<int> v1,vector<int> v2,vector<int> v3)
{
    int len =v3.size();
    for(int i=0;i<len;i++)
    {
      v2.insert(v2.end(),v1.begin()+i*4,v1.begin()+i*4+4);  
    }
    return v2;
}
//实现group by t1.id2,t2.id2,并且是按照max(t1.id1),min(t2.id1)进行group by
vector<int> group_by(vector<int> v1)
{   
    vector<int> res;
    vector<int> row_res;
    unordered_map<int,int> t1_id2;
    unordered_map<int,int> t2_id2;
    unordered_map<int,int>::iterator t1;
    unordered_map<int,int>::iterator t2;
    int row_plus=0;
    int v1_row_len=v1.size()/4;
    //希尔排序
     for (int gap =v1_row_len/ 2; gap > 0; gap /= 2)
        {
            for (int i = gap*4; i < v1.size(); i+=4) {
                for (int j = i; j - gap*4 >= 0 && v1[j - gap*4+1] > v1[j+1]; j -=gap*4) {
                    swap(v1[j - gap*4+1], v1[j+1]);
                    swap(v1[j - gap*4+0], v1[j+0]);
                    swap(v1[j - gap*4+2], v1[j+2]);
                    swap(v1[j - gap*4+3], v1[j+3]);
                }
            }
        }
 cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;      
    for(int i=0;i<v1_row_len;i++)
    {   
        if(t1_id2.count(v1[i*4+1])==0)
        {
            row_res.push_back(i);
            t2_id2.clear();
            t1_id2.insert(make_pair(v1[i*4+1],i));
            t2_id2.insert(make_pair(v1[i*4+3],i));
        }
        else
        {
            
            if(t2_id2.count(v1[i*4+3])==0)
            {
                row_res.push_back(i);
           //     row_plus++;
                t2_id2.insert(make_pair(v1[i*4+3],i));
               
            }
            else
            {  
                  int group_min,group_min2; 
                //   t1=t1_id2.find(v1[i*4+1]);
                  t2=t2_id2.find(v1[i*4+3]);
                  int j=t2->second;
                  if(v1[i*4+1]==v1[j*4+1] && v1[i*4+3]==v1[j*4+3])
                   { 
                     if (v1[i*4+2]< v1[j*4+2])
                        {
                            group_min=v1[i*4+2];
                            group_min2=v1[i*4+3];
                        }
                     else
                         {
                            group_min=v1[j*4+2];
                            group_min2=v1[j*4+3];
                         }
                      if(v1[i*4+0]>v1[j*4+0])
                        {  
                            v1[j*4]=v1[i*4];  
                        }
                      v1[j*4+2]=group_min;
                      v1[j*4+3]=group_min2;    
                    } 
            }
        }
    }
    for(int i=0;i<row_res.size();i++)
    {
      res.insert(res.end(),v1.begin()+row_res[i]*4,v1.begin()+row_res[i]*4+4);  
    }
    return res;
}
//定义sort的cmp方法用于二维数组排序,对应实现order by max(t1.id1),t2.id2,t1.id2;
void order_by(vector<int> &v1)
{
    int row_v1=v1.size()/4;
    for(int i=0;i<row_v1;i++)
    {
        int min=i;
        for(int j=i;j<row_v1;j++)
        {
            if(v1[j*4]<v1[min*4])
            {
                min=j;
            }
            else if (v1[j*4]==v1[min*4] && v1[j*4+3]<v1[min*4+3])
            {
                min=j;
            }
            else if (v1[j*4]==v1[min*4] && v1[j*4+3]==v1[min*4+3] && v1[j*4+1]<v1[min*4+1])
            {
                min=j;
            }
        }
        swap(v1[i*4],v1[min*4]);
        swap(v1[i*4+3],v1[min*4+3]);
        swap(v1[i*4+1],v1[min*4+1]);
        swap(v1[i*4+2],v1[min*4+2]);

    }   
}
int main()
{   
    vector<int> result;
    vector<int> tmp;
    vector<vector<int>> vec_input1;
    vector<vector<int>> vec_input2;
    ifstream input1("/media/chen/F/C++/mycode/ztedatabase/input3.csv");
    ifstream input2("/media/chen/F/C++/mycode/ztedatabase/input4.csv");
    string line1;
    string line2;

    //从文件input1中读取数据至数组vec_input1
    while(getline(input1,line1))
    {   string s1; 
        istringstream s1_cin(line1);

        while(getline(s1_cin,s1,','))
        { 
           tmp.push_back(atoi(s1.c_str()));

        }
        vec_input1.push_back(tmp);
        tmp.clear();
        line1.clear();
    }
    input1.close();
  
    //从文件input2中读取数据至数组vec_input2
    while(getline(input2,line2))
    {   string s2; 
        istringstream s2_cin(line2);

        while(getline(s2_cin,s2,','))
        { 
           tmp.push_back(atoi(s2.c_str()));

        }
        vec_input2.push_back(tmp);
        tmp.clear();
        line2.clear();
    }
    vector<int>().swap(tmp);
    input2.close();
   cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
    result=join_on(vec_input1,vec_input2);
   cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
   int a=result.size()/4;
    vector<vector<int>>().swap(vec_input1);
    vector<vector<int>>().swap(vec_input2);
    result=group_by(result);
    order_by(result);
   
    for(int i=0;i<result.size()/4;i++)
    {
      cout<<result[i*4]<<','<<result[i*4+2]<<endl;
    }
     cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
    vector<int>().swap(result);
    return 0;
}