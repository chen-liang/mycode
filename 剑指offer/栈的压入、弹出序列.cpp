#include<vector>
#include<stack>
#include<iostream>
using namespace std;
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        vector<int> result;
        if(pushV.size()==0||popV.size()==0) return false;
        int j=0;
        for(int i=0;i<pushV.size();i++)
        {
            result.push_back(pushV[i]);
            while(result.back()==popV[j]&&!result.empty())
            {
                result.pop_back();
                j++;
            }
        }
        return result.empty();
    }
};
int main()
{
    bool res;
    vector<int> a={1,2,3,4,5},b={4,5,3,2,1};
    Solution A;
    res=A.IsPopOrder(a,b);
    cout<<res<<endl;
    return 0;
}