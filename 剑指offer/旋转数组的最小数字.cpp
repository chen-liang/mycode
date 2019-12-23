#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size()==0) return 0;
        sort(rotateArray.begin(),rotateArray.end());
        return rotateArray[0];
    }
};