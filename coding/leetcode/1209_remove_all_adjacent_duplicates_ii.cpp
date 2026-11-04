// LC 1209 Remove All Adjacent Duplicates in String II
// Date: 2026-11-03 · Time: ~27 min · AI: coached on approach
// Pattern: stack of (char, count) · Time O(n) · Space O(n)
// Miss: none. Own insight: run-length encode as (char, freq) nodes; merges only
//       ever happen with the left neighbour, so a stack is enough.
//
// Hook: Zuma / Candy Crush. A ball joins the end of the chain; if it matches the
//       last group, the group grows; at k the group vanishes and the next ball
//       lands on whatever group is now at the end (chain reaction).

#include <cassert>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        if (k == 1)
            return "";  // push_back({c, 1}) never checks k, so k == 1 needs a guard

        vector<pair<char, int>> freq_stack;
        freq_stack.reserve(s.size());

        for (char c : s) {
            if (!freq_stack.empty() && freq_stack.back().first == c) {
                if (++freq_stack.back().second == k)
                    freq_stack.pop_back();
            } else {
                freq_stack.push_back({c, 1});
            }
        }

        // Review note: it's a vector, so build front to back; no pop + reverse needed.
        string res;
        res.reserve(s.size());
        for (const auto& [c, num] : freq_stack)
            res.append(num, c);
        return res;
    }
};

int main() {
    Solution sol;
    assert(sol.removeDuplicates("abcd", 2) == "abcd");
    assert(sol.removeDuplicates("deeedbbcccbdaa", 3) == "aa");
    assert(sol.removeDuplicates("pbbcggttciiippooaais", 2) == "ps");
    assert(sol.removeDuplicates("abbbaa", 3) == "");    // chain reaction
    assert(sol.removeDuplicates("eeee", 3) == "e");     // run longer than k
    return 0;
}
