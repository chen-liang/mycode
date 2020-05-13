#include<vector>
using namespace std;
class Solution {
public:
    int rectCover(int number) {
        vector<int> f(number+1,0);
        f[1]=1;f[2]=2;
        for(int i=3;i<number+1;i++)
        {
            f[i]=f[i-1]+f[i-2];
        }
        return f[number];
    }
};