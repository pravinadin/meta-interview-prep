// LC 938 Range Sum of BST
// Date: 2026-11-04 · AI: reviewed
// Pattern: BST-pruned DFS · Time O(h + k) typical, O(n) worst · Space O(h)
// Miss: first version visited every node (in-order, no pruning); second had
//       asymmetric conditions (> low but <= high) and visited 18 needlessly.
//
// Duplicates: loosen the comparison on the side where equal values live.
//   dups go left  -> left: val >= low, right: val <  high
//   dups go right -> left: val >  low, right: val <= high
//   unknown       -> left: val >= low, right: val <= high (always correct)
//   LC 938 guarantees unique values, so both sides are strict.
// Hook: two fences. Below the low fence, don't turn left; above the high
//       fence, don't turn right; add everything between.

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        int res = 0;
        dfs(root, low, high, res);
        return res;
    }

private:
    void dfs(TreeNode* node, int low, int high, int& result) {
        if (!node)
            return;
        if (node->val > low)
            dfs(node->left, low, high, result);   // left subtree can still reach low
        if (node->val >= low && node->val <= high)
            result += node->val;
        if (node->val < high)
            dfs(node->right, low, high, result);  // right subtree can still reach high
    }
};

int main() {
    Solution sol;
    /*        10
     *       /  \
     *      5    15
     *     / \     \
     *    3   7     18
     */
    TreeNode n3(3), n7(7), n18(18);
    TreeNode n5(5, &n3, &n7);
    TreeNode n15(15, nullptr, &n18);
    TreeNode root(10, &n5, &n15);
    assert(sol.rangeSumBST(&root, 7, 15) == 32);
    assert(sol.rangeSumBST(&root, 0, 100) == 58);
    assert(sol.rangeSumBST(&root, 11, 14) == 0);
    return 0;
}
