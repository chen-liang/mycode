#include<vector>
#include<iostream>
#include<queue>
using namespace std;
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
class Solution {
public:
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        queue<TreeNode*> tmp;
        vector<int> res;
        tmp.push(root);
        while(!tmp.empty()){
            root=tmp.front();
            tmp.pop();
            if(!root)
                continue;
            res.push_back(root->val);
            tmp.push(root->left);
            tmp.push(root->right);
             
             
        }
        return res;
 
    }
};
int main()
{
    Solution A;
    TreeNode* root=NULL;
    bool a=!root;
    cout<<a;
    return 0;

}