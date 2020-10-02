#include<iostream>
#include<vector>
using namespace std;

class KthLargest {
    int kth;
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        int cnt;
        
        TreeNode(int x, TreeNode *lt=NULL, TreeNode *rt=NULL):
            val(x),left(lt),right(rt),cnt(0) {}
        ~TreeNode() {}
    };
    
    TreeNode *root;
    
    void insert(int x,TreeNode *&t){
        if(t==NULL) t=new TreeNode(x,NULL,NULL);
        else if(x<t->val) insert(x,t->left);
        else if(t->val<x) insert(x,t->right);
        // else ++t->cnt;
        //t->cnt = ((t->left!=NULL)?t->left->cnt:0) + ((t->right!=NULL)?t->right->cnt:0) + 1;
        ++t->cnt;
    }
    
public:
    KthLargest(int k, vector<int>& nums) {
        kth = k;
        root = NULL;
        
        for(int i=0;i<nums.size();++i)
            insert(nums[i],root);
        
    }
    
    int add(int val) {
        insert(val,root);
        
        // Search
        int k = kth;
        TreeNode *p = root;
        while(k>=1){
            if(p->right!=NULL){
                if(k>p->right->cnt)
                    k -= p->right->cnt;
                else if(k-p->right->cnt==1)
                    break;      //就是这个节点
                else {p = p->right; continue;}
            }
            k -= p->cnt - (p->left!=NULL?p->left->cnt:0) - (p->right!=NULL?p->right->cnt:0);
            if(k>=1){      //去掉本节点
                p = p->left;
            } else break;
        }
        
        return p->val;
    }
};

int main(){
    // int k = 3;
    // vector<int> arr = {4,5,8,2};
    // KthLargest kthLargest(k, arr);
    // cout << kthLargest.add(3) << ' ';   // returns 4
    // cout << kthLargest.add(5) << ' ';   // returns 5
    // cout << kthLargest.add(10) << ' ';  // returns 5
    // cout << kthLargest.add(9) << ' ';   // returns 8
    // cout << kthLargest.add(4) << ' ';   // returns 8
    int k = 3;
    vector<int> arr ={5,-1};
    KthLargest kthLargest(k, arr);
    cout << kthLargest.add(2) << ' ';   // returns 4
    cout << kthLargest.add(1) << ' ';   // returns 5
    cout << kthLargest.add(-1) << ' ';  // returns 5
    cout << kthLargest.add(3) << ' ';   // returns 8
    cout << kthLargest.add(4) << ' ';   // returns 8
    return 0;
}