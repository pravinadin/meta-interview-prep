// LC 236 Lowest Common Ancestor of a Binary Tree
// Date: 2026-11-04 · AI: reviewed
// Pattern: post-order DFS, report "what I found below me" · Time O(n) · Space O(h)
// Miss: none.
//
// Notes: compare node POINTERS, not values (duplicates don't matter).
//   Stopping at root == p is safe only because both nodes are guaranteed to
//   exist. Follow-up LC 1644 (they may not exist): the early return becomes a
//   bug; traverse fully and count how many were found.
// Hook: a search party. Each node asks both branches "found anyone?" and
//   passes up what it heard; the first node hearing "yes" from both sides is
//   where the paths meet.

#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(x), left(l), right(r) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q)
            return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
            return root;             // p and q are in different subtrees
        return left ? left : right;  // pass up whichever was found, or null
    }
};

int main() {
    Solution sol;
    /*            3
     *          /   \
     *         5     1
     *        / \   / \
     *       6   2 0   8
     *          / \
     *         7   4
     */
    TreeNode n6(6), n7(7), n4(4), n0(0), n8(8);
    TreeNode n2(2, &n7, &n4);
    TreeNode n5(5, &n6, &n2);
    TreeNode n1(1, &n0, &n8);
    TreeNode root(3, &n5, &n1);
    assert(sol.lowestCommonAncestor(&root, &n5, &n1) == &root);
    assert(sol.lowestCommonAncestor(&root, &n5, &n4) == &n5);  // ancestor of itself
    assert(sol.lowestCommonAncestor(&root, &n6, &n4) == &n5);
    return 0;
}
