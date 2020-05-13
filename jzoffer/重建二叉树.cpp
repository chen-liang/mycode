#include<vector>
using namespace std;

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin)
{
    if (pre.empty() || vin.empty())
        return NULL;
    vector<int> pre_left, pre_right, vin_left, vin_right;
   // int val = pre[0];
    TreeNode* root = new TreeNode(pre[0]);
    int i,m=0;
  
    for (i = 0; i < vin.size(); ++i)
    {
        if (pre[0] == vin[i])

            break;
    }
      m=i;
    for (int j = 0; j < vin.size(); ++j){
  
        if (j < m){
            
            pre_left.push_back(pre[j + 1]);
            vin_left.push_back(vin[j]);
        }
        else if (j > m)
        {

            pre_right.push_back(pre[j]);
            vin_right.push_back(vin[j]);
        }
    }
    root->left = reConstructBinaryTree(pre_left, vin_left);
    root->right = reConstructBinaryTree(pre_right, vin_right);
    return root;
}
  
};
