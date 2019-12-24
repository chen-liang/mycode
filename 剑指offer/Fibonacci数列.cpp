#include<iostream>
using namespace std;
class Solution {
public:
    int Fibonacci(int n) {
        if(n<1)
        {
             return 0;
        }
        else if(n==1||n==2) return 1;
       /* else if(n>=3&&n<=39)
        {
           return Fibonacci(n-1)+Fibonacci(n-2);
        }
        */
       int res=1,pre=1,temp=0;
       for(int i=3;i<=n;i++)
       {
           temp=res;
           res=res+pre;
           pre=temp;
       }
       return res;
       
    }
};
int main()
{
    Solution S;
    int n=39;
    cout<<S.Fibonacci(n)<<endl;
}