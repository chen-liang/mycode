#include<vector>
using namespace std;
class Solution {
public:
    void reOrderArray(vector<int> &array) {
        vector<int> result;
        int length=array.size();
        for(int i=0;i<length;++i)
        {
            if(array[i]%2==1)
            {
                result.push_back(array[i]);
            }
        }
       for(int i=0;i<length;++i)
        {
             if(array[i]%2==0)
            {
                result.push_back(array[i]);
            }
        }
        array=result;
    }
    
};