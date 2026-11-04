// LC 1650 Lowest Common Ancestor of a Binary Tree III (parent pointers, no root)
// Date: 2026-11-04 · AI: reviewed
// Pattern: two pointers, switch heads (= LC 160 linked-list intersection)
//          · Time O(h) · Space O(1)
// Miss: none.
//
// Why it works: a walks p->root, then q->merge; b walks q->root, then p->merge.
//   Both cover (dp + dq + 1) steps counting the null hop, so they reach the merge
//   node on the same step. Terminates because both nodes are in the same tree
//   (worst case they meet at the root).
// Baseline to state first: put p's ancestors in a hash set, walk up from q
//   until you hit one; O(h) time, O(h) space.
// Hook: two runners swap tracks. Each runs its own track, then the other's;
//   same total distance, so they arrive at the junction together.

#include <cassert>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
    explicit Node(int v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node* q) {
        Node *a = p, *b = q;
        while (a != b) {
            a = a ? a->parent : q;
            b = b ? b->parent : p;
        }
        return a;
    }
};

static void link(Node& parent, Node* l, Node* r) {
    parent.left = l;
    parent.right = r;
    if (l) l->parent = &parent;
    if (r) r->parent = &parent;
}

int main() {
    Solution sol;
    /*            3
     *          /   \
     *         5     1
     *        / \
     *       6   2
     *          / \
     *         7   4
     */
    Node n3(3), n5(5), n1(1), n6(6), n2(2), n7(7), n4(4);
    link(n3, &n5, &n1);
    link(n5, &n6, &n2);
    link(n2, &n7, &n4);
    assert(sol.lowestCommonAncestor(&n6, &n4) == &n5);  // different depths
    assert(sol.lowestCommonAncestor(&n5, &n1) == &n3);  // same depth
    assert(sol.lowestCommonAncestor(&n5, &n4) == &n5);  // p is ancestor of q
    assert(sol.lowestCommonAncestor(&n4, &n4) == &n4);  // p == q
    return 0;
}
