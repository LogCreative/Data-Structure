/*
 * @lc app=leetcode.cn id=572 lang=java
 *
 * [572] 另一棵树的子树
 */

/**
 * Definition for a binary tree node.
 */
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

// @lc code=start

class Solution {

    private boolean isSameTree(TreeNode root, TreeNode subRoot) {
        if (subRoot == null) {
            if (root == null) return true;
            return false;
        }
        if (root == null && subRoot != null) return false;
        if (subRoot.val != root.val) return false;
        return isSameTree(subRoot.left, root.left) && isSameTree(subRoot.right, root.right);
    }

    public boolean isSubtree(TreeNode root, TreeNode subRoot) {
        if (subRoot == null) return true;
        if (root == null) return false;
        if (isSameTree(root, subRoot)) return true;
        if (isSubtree(root.left, subRoot)) return true;
        if (isSubtree(root.right, subRoot)) return true;
        return false;
    }
}
// @lc code=end

// 我们可以引入两个空值 lNull 和 rNull，当一个节点的左孩子或者右孩子为空的时候，就插入这两个空值，这样深度优先搜索序列就唯一对应一棵树。=> 转换为匹配子串的问题。