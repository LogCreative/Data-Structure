#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* divide(vector<int> nums,int start,int end){
    TreeNode *root;
    if(end<start) root = NULL;
    else 
    switch(end-start){
        // case 0: root = NULL; break;
        case 0: root = new TreeNode(nums[start]); break;
        case 1:
            root = new TreeNode(nums[end]);
            root->left = new TreeNode(nums[start]); break;
        case 2:
            root = new TreeNode(nums[start+1]);
            root->left = new TreeNode(nums[start]);
            root->right = new TreeNode(nums[end]); break;
        default:
            int mid=(end+start)/2;
            root = new TreeNode(nums[mid]);
            root->left = divide(nums,start,mid-1);
            root->right = divide(nums,mid+1,end); break;
    }
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    int size = nums.size();
    if(size==0) return NULL;
    return divide(nums,0,size-1);
}

int main(){
    vector<int> vec = {0,1,2,3,4,5,6,7};
    sortedArrayToBST(vec);
    return 0;
}