// LC 71 Simplify Path
// Date: 2026-11-03 · Time: ~12 min · AI: no (looked up getline/strtok syntax only)
// Pattern: stack of names · Time O(n) · Space O(n)
// Miss: none in C++. The C version (71_simplify_path.c) had two issues; see
//       tracker/error-log.md.
//
// Hook: it's `cd` in a shell. "" or "." = stay, ".." = cd .. (stop at /),
//       anything else = cd name, then pwd. Only the exact strings "." and ".."
//       are special: "..." and ".config" are names.

#include <cassert>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> dirStack;           // vector, not std::stack: pop back, join front to back

        istringstream ss(path);            // input-only stream
        string component;

        while (getline(ss, component, '/')) {
            if (component.empty() || component == ".") {
                continue;                  // "" from leading or doubled '/'
            } else if (component == "..") {
                if (!dirStack.empty()) {   // can't go above root
                    dirStack.pop_back();
                }
            } else {
                dirStack.push_back(component);
            }
        }

        string result;
        for (const auto& dir : dirStack) {
            result += "/" + dir;
        }

        return result.empty() ? "/" : result;
    }
};

int main() {
    Solution sol;
    assert(sol.simplifyPath("/home/") == "/home");
    assert(sol.simplifyPath("/../") == "/");
    assert(sol.simplifyPath("/home//foo/") == "/home/foo");
    assert(sol.simplifyPath("/a/./b/../../c/") == "/c");
    assert(sol.simplifyPath("/.../a/../b/c/../d/./") == "/.../b/d");  // "..." is a name
    assert(sol.simplifyPath("/home/.config") == "/home/.config");      // so is ".config"
    return 0;
}
