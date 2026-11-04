// LC 314 Binary Tree Vertical Order Traversal
// Date: 2026-11-03 · Time: ~19 min · AI: reviewed
// Pattern: BFS with column index · Time O(n) · Space O(n)
// Miss: none. Cleanups from review: don't reuse minCol with a flipped meaning;
//       move column vectors instead of copying.
//
// Why it's O(n): BFS gives top-to-bottom, left-to-right order for free; columns
//       are contiguous (each edge changes the column by exactly 1), so index by
//       col - minCol instead of sorting.
// Hook: read the tree like a page, drop each node into a bucket on the floor.

#include <cassert>
#include <queue>
#include <unordered_map>
#include <utility>
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
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root)
            return {};

        queue<pair<TreeNode*, int>> nodeQ;
        nodeQ.push({root, 0});
        unordered_map<int, vector<int>> col_map;
        int maxCol = 0;
        int minCol = 0;

        while (!nodeQ.empty()) {
            auto [node, col] = nodeQ.front();
            nodeQ.pop();
            maxCol = max(maxCol, col);
            minCol = min(minCol, col);
            col_map[col].push_back(node->val);

            if (node->left)
                nodeQ.push({node->left, col - 1});
            if (node->right)
                nodeQ.push({node->right, col + 1});
        }

        vector<vector<int>> res(maxCol - minCol + 1);
        for (auto& [col, vec] : col_map)
            res[col - minCol] = std::move(vec);
        return res;
    }
};

int main() {
    Solution sol;
    /*        3
     *       / \
     *      9   20
     *         /  \
     *        15   7
     */
    TreeNode n15(15), n7(7), n9(9);
    TreeNode n20(20, &n15, &n7);
    TreeNode root(3, &n9, &n20);
    vector<vector<int>> want = {{9}, {3, 15}, {20}, {7}};
    assert(sol.verticalOrder(&root) == want);
    assert(sol.verticalOrder(nullptr).empty());
    return 0;
}
