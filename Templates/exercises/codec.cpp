#include<iostream>
#include<queue>
#include<string>
using namespace std;

// 看题解吧 仅供欣赏。

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == NULL) return "";
        queue<TreeNode*> que;
        que.push(root);
        TreeNode *current;
        string output = "";
        while(!que.empty()){
            current = que.front();que.pop();
            if(current == NULL){output += "null"; output += ",";}
            else {
                output += current->val; output += ",";
                que.push(current->left);
                que.push(current->right);
            }
        }
        //退一格
        if(output!="") output.pop_back();
        return output;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data=="") return (TreeNode*)NULL;
        vector<string> s = split(data);
        queue<TreeNode *> que;
        if(s[0]=="null")
            return (TreeNode*)NULL;
        bool flag = false;
        TreeNode *root = new TreeNode(stoi(s[0]));
        que.push(root);
        int current = 1;
        TreeNode *p;
        while(current<s.size()){
            if(flag){
                if(s[current]!="null"){
                    p = new TreeNode(stoi(s[current]));
                    que.front()->right = p;
                    que.push(p);
                }
                que.pop();
            } else {
                if(s[current]!="null"){
                    p = new TreeNode(stoi(s[current]));
                    que.front()->left = p;
                    que.push(p);
                }
            }
            flag = !flag;
            ++current;
        }
        return root;
    }

     vector<string> split(string &data){
        int start=0;
        vector<string> res;
        while(1){
            auto end = data.find(',',start);
            if(end==string::npos)break;
            res.push_back(data.substr(start,end-start));
            start=end+1;
        }
        return move(res);
    }

    int stoi(string s){
        int current = 0;
        if(s[0]=='-'){
            for(int i = 1;i<s.size();++i){
                int tmp = s[i];
                current = current *10 + tmp;
            }
            current = -current;
        } else{
            for(int i = 0;i<s.size();++i){
                int tmp = s[i];
                current = current *10+tmp;
            }
        }
        return current;
    }
};

int main(){
    Codec c;
    TreeNode* root = c.deserialize("[1,2,3,null,null,4,5]");
    cout<<root->val;
    return 0;
}