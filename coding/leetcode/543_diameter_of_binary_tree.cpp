// LC 543 Diameter of Binary Tree
// Date: 2026-11-04 · AI: reviewed
// Pattern: post-order DFS, return one thing / record another · Time O(n) · Space O(h)
// Miss: none. Simplification from review: return height in NODES so null
//       children need no special case; L + R is still the edge count.
//
// Hook: arm span. Each node writes its arm span (left arm + right arm) on a
//       shared scoreboard and reports only its LONGER arm to its parent
//       (a path can't fork). Same skeleton as LC 124.
// Follow-up: depth 1e4 is fine on an 8 MB stack; at 1e6, go iterative
//       (explicit stack + node -> height map).

#include <algorithm>
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
    int diameterOfBinaryTree(TreeNode* root) {
        int max_diam = 0;
        height(root, max_diam);
        return max_diam;
    }

private:
    int height(TreeNode* node, int& diam) {
        if (!node) return 0;
        int L = height(node->left, diam);   // nodes on the deepest left path
        int R = height(node->right, diam);
        diam = max(diam, L + R);            // edges in the path bending here
        return 1 + max(L, R);
    }
};

int main() {
    Solution sol;
    /*        1
     *       / \
     *      2   3
     *     / \
     *    4   5
     */
    TreeNode n4(4), n5(5), n3(3);
    TreeNode n2(2, &n4, &n5);
    TreeNode root(1, &n2, &n3);
    assert(sol.diameterOfBinaryTree(&root) == 3);

    // Diameter not through the root: left-heavy subtree.
    TreeNode a(1), b(2);
    TreeNode e(5, &a, nullptr), f(6, nullptr, &b);
    TreeNode g(7, &e, &f);        // path a-e-g-f-b = 4 edges
    TreeNode top(8, &g, nullptr); // root adds only 1 above g
    assert(sol.diameterOfBinaryTree(&top) == 4);

    TreeNode single(1);
    assert(sol.diameterOfBinaryTree(&single) == 0);
    return 0;
}
