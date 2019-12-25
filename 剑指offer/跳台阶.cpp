#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int jumpFloor(int number) {
        vector<int> f(number+1,1);
       // if(number<=0) return 0;
        f[1]=1;f[2]=2;
        for(int i=3;i<number+1;i++)
        {
            f[i]=f[i-1]+f[i-2];
            
        }
        return f[number];
    }
};
int main()
{
    Solution S;
    int n=39;
    cout<<S.jumpFloor(n)<<endl;
}