// LC 227 Basic Calculator II
// Date: 2026-11-03 · Time: ~60 min (approach discussion + code) · AI: coached on approach
// Pattern: stack + pending operator · Time O(n) · Space O(n); O(1) variant below
// Miss: needed hints on precedence (* and / are one level, left to right),
//       on when to apply the pending op, and on flushing the last number.
//       See tracker/error-log.md.
//
// Hook: the cashier's receipt. + adds a line, - adds a refund line,
//       * and / edit the LAST line, total the receipt at checkout.
//       "Look back, edit last, sum at the end."
//       O(1): only the last line is wet ink; add the rest as it dries.

#include <cassert>
#include <cctype>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // Stack version: every entry is a signed number; answer = sum of the stack.
    int calculate(string s) {
        const int n = static_cast<int>(s.size());
        vector<long long> st;
        long long num = 0;
        char op = '+';                              // pending op for the first number
        for (int i = 0; i <= n; ++i) {
            char c = i < n ? s[i] : '+';            // sentinel flushes the last number
            if (isdigit(static_cast<unsigned char>(c))) {
                num = num * 10 + (c - '0');
                continue;
            }
            if (c == ' ') continue;                 // spaces never trigger the apply step
            switch (op) {                           // apply the op BEHIND the number
                case '+': st.push_back(num); break;
                case '-': st.push_back(-num); break;
                case '*': st.back() *= num; break;
                case '/': st.back() /= num; break;  // C++ truncates toward zero, as required
            }
            op = c;
            num = 0;
        }
        return static_cast<int>(accumulate(st.begin(), st.end(), 0LL));
    }

    // O(1)-space version: result = everything below the stack top, last = stack top.
    int calculateO1(string s) {
        const int n = static_cast<int>(s.size());
        long long result = 0, last = 0, num = 0;
        char op = '+';
        for (int i = 0; i <= n; ++i) {
            char c = i < n ? s[i] : '+';
            if (isdigit(static_cast<unsigned char>(c))) {
                num = num * 10 + (c - '0');
                continue;
            }
            if (c == ' ') continue;
            switch (op) {
                case '+': result += last; last =  num; break;
                case '-': result += last; last = -num; break;
                case '*': last *= num; break;
                case '/': last /= num; break;
            }
            op = c;
            num = 0;
        }
        return static_cast<int>(result + last);
    }
};

int main() {
    Solution sol;
    struct Case { const char* in; int want; };
    const Case cases[] = {
        {"3 + 5 * 2 - 4", 9},   // walkthrough example
        {"3+2*2", 7},
        {" 3/2 ", 1},           // leading/trailing spaces, integer division
        {"8/4*2", 4},           // * and / are one level, left to right
        {"3-5/2", 1},           // negative top, inexact division: truncate toward 0
        {"42", 42},             // single multi-digit number, no operators
        {"0", 0},
    };
    for (const auto& c : cases) {
        assert(sol.calculate(c.in) == c.want);
        assert(sol.calculateO1(c.in) == c.want);
    }
    return 0;
}
