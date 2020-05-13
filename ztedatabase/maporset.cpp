#include <stdio.h>
#include<vector>
#include<iostream>
#include<ctime>
#include <iomanip>
#include <string.h>
#include <sstream>
using namespace std;
struct CSVDATA
{
    int id1;
    int id2;
    int id3;
} ;
vector<CSVDATA> fread_analyse(char const *file)
{
    FILE *fp;
    fp=fopen(file,"r");
        fseek(fp,0,SEEK_END); //把指针移动到文件的结尾
        unsigned int len = ftell(fp); //获取文件长度
        rewind(fp); //把指针移动到文件开头 
        char *pbuf=new char[len+1];
        pbuf[len]=0;
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
int main()
{
      vector<struct CSVDATA> csvdata1;   //存储t1
    vector<struct CSVDATA> csvdata2;   //存储t2
    char const *file1="/media/chen/F/C++/mycode/ztedatabase/input5.csv";
    char const *file2="/media/chen/F/C++/mycode/ztedatabase/input6.csv";
     csvdata1=fread_analyse(file1);
     csvdata2=fread_analyse(file2);
     int a=csvdata1.size(),b=csvdata2.size();
      cout<<a<<endl<<b<<endl;
   cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;   
    return 0;
}