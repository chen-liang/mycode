#include<iostream>
#include<set>
using namespace std;
int main()
{
   int n,temp;
   set<int> sa,sb,sJiao,sBing,sCha;
   set<int>:: iterator it_a,it_b,it;
   
   //输入 
   cin>>n;
   while(n--)
   {
       cin>>temp;
       sa.insert(temp);          
   }
   cin>>n;
   while(n--)
   {
       cin>>temp;
       sb.insert(temp);          
   }
   
   //求交 
   it_a=sa.begin();
   it_b=sb.begin();
   while(it_a!=sa.end() && it_b!=sb.end())
   {
          if(*it_a < *it_b)
              it_a++;
          else if(*it_b > *it_a)
              it_b++;
          else
          {
              sJiao.insert(*it_a);    
              it_a++;
              it_b++;
          }              
   }
   //求并
   it_a=sa.begin();
   while(it_a!=sa.end())
   {
       sBing.insert(*it_a);
       it_a++;                     
   } 
   it_b=sb.begin();
   while(it_b!=sb.end())
   {
       sBing.insert(*it_b);
       it_b++;               
   }
   //求差 
   sCha=sa;
   it_b=sb.begin();
   while(it_b!=sb.end())
   {
       sCha.erase(*it_b);
       it_b++;             
   }
   
   //输出 
   it=sJiao.begin();
   while(it!=sJiao.end())
   {
       cout<<*it<<endl;   
       it++;                
   }
   cout<<endl;
   
   it=sBing.begin();
   while(it!=sBing.end())
   {
       cout<<*it<<endl;   
       it++;                
   }
   cout<<endl;
   
   it=sCha.begin();
   while(it!=sCha.end())
   {
       cout<<*it<<endl;   
       it++;                
   }
   cout<<endl;
   system("pause");
   return 0;
}
/*
5
1 4 2 15 -23
4
2 5 15 4
*/
