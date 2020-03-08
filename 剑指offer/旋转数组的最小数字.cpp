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
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size()==0) return 0;
        int left=0,right=rotateArray.size()-1,mid;
        while(left<right)
        {
            mid=left+(right-left)/2;
            if(rotateArray[right]<rotateArray[mid])
            {
                left=mid+1;
            }
            else if(rotateArray[right]==rotateArray[mid])
            {
                right=right-1;
            }
            else{
                right=mid;
            }
        }
        return rotateArray[left];
    }
};