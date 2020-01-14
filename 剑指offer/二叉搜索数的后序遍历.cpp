#include<vector>
using namespace std;
/*�ݹ鷨*/

class Solution {
    bool judge(vector<int>& a, int l, int r){
        if(l >= r) return true;
        int i = r;
        while(i > l && a[i - 1] > a[r]) --i;
        for(int j = i - 1; j >= l; --j) if(a[j] > a[r]) return false;
        return judge(a, l, i - 1) && (judge(a, i, r - 1));
    }
public:
    bool VerifySquenceOfBST(vector<int> a) {
        if(!a.size()) return false;
        return judge(a, 0, a.size() - 1);
    }
};
class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        int size=sequence.size();
        if(size==0) return false;
        int i=0;
        while(--size)
        {
            while(sequence[i++]<sequence[size]) ;
            while(sequence[i++]>sequence[size]) ;
            if(i<size) return false;
            i=0;
        }
        return true;
    }
};