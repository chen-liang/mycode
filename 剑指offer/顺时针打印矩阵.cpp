/*
����һ�����󣬰��մ���������˳ʱ���˳�����δ�ӡ��ÿһ�����֣�
���磬�����������4 X 4���� 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
�����δ�ӡ������1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
*/
#include<vector>
#include<math.h>
using namespace std;
class Solution {
public:
    vector<int> printMatrix(vector<vector<int>> matrix) {
        int row=matrix.size(),col=matrix[0].size();
        vector<int> result;
        int left=0,top=0,right=col-1,bottom=row-1;
        if(row==0||col==0) return result;
        while(left<=right&&top<=bottom)
        {
            for(int i=left;i<=right;i++) result.push_back(matrix[top][i]);
            for(int i=top+1;i<=bottom;i++) result.push_back(matrix[i][right]);
            if(top!=bottom) for(int i=right-1;i>=left;i--) result.push_back(matrix[bottom][i]);
            if(left!=right) for(int i=bottom-1;i>top;i--) result.push_back(matrix[i][left]);
            left++;top++;right--;bottom--;
        }
        return result;
    }
};