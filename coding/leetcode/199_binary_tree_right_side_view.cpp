// LC 199 Binary Tree Right Side View
// Date: 2026-11-04 · AI: no
// Pattern: BFS with level-size snapshot · Time O(n) · Space O(w), w = max width
// Miss: none.
//
// Follow-up: DFS visiting right before left, recording a node when
//       depth == res.size(), gives O(h) space. Better for wide, shallow trees;
//       worse for a skewed tree (recursion depth n).
// Hook: a building seen from the right. Freeze each floor's headcount
//       (levelSize); the last person on the floor is the one at the window.

#include <cassert>
#include <queue>
#include <vector>
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root)
            return res;

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();  // nodes currently queued = this whole level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                if (i == levelSize - 1)
                    res.push_back(node->val);  // last node on this level: visible
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    /*      1
     *     / \
     *    2   3
     *     \   \
     *      5   4
     */
    TreeNode n5(5), n4(4);
    TreeNode n2(2, nullptr, &n5);
    TreeNode n3(3, nullptr, &n4);
    TreeNode root(1, &n2, &n3);
    assert((sol.rightSideView(&root) == vector<int>{1, 3, 4}));

    TreeNode b(2);
    TreeNode a(1, &b);  // rightmost node is a LEFT child
    assert((sol.rightSideView(&a) == vector<int>{1, 2}));
    return 0;
}
