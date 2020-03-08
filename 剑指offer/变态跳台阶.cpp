#include<vector>
#include<iostream>
using namespace std;
class Solution
{
    public:
        int Jump(int number)
        {
            vector<int> f(number,0);
            f[1]=1;f[2]=2;
            for(int i=3;i<number+1;i++)
            {
                f[i]=2*f[i-1];
            }
            return f[number];
        }
};
int main()
{  
    Solution S;
    int y=30;
    cout<<S.Jump(y);
    return 0;
}