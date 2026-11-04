// LC 468 Validate IP Address
// Date: 2026-11-03 · Time: ~27 min · AI: reviewed (first IPv4 draft had bugs)
// Pattern: frame-then-fields parsing · Time O(n) · Space O(1) besides the token
// Miss: first draft trusted getline, which swallows a trailing delimiter
//       ("1.1.1.1." passed) and returns empty tokens that skipped every check
//       ("1..1.1" passed). See tracker/error-log.md.
//
// Hook: check the frame before the fields. Like a packet parser that checks the
//       header length before reading any TLV: count delimiters first, then
//       validate each field, then confirm the field count.

#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>
#include <string>
using namespace std;

class Solution {
public:
    string validIPAddress(string queryIP) {
        if (validIpv4(queryIP))
            return "IPv4";
        if (validIpv6(queryIP))
            return "IPv6";
        return "Neither";
    }

private:
    bool validIpv4(const string& ip) {
        if (count(ip.begin(), ip.end(), '.') != 3)
            return false;  // framing: exactly 3 dots

        istringstream ss(ip);
        string comp;
        int fields = 0;
        while (getline(ss, comp, '.')) {
            ++fields;
            if (comp.empty() || comp.size() > 3)
                return false;  // empty, or too long (also bounds val: no overflow)
            if (comp.size() > 1 && comp[0] == '0')
                return false;  // leading zero
            int val = 0;
            for (char c : comp) {
                if (!isdigit(static_cast<unsigned char>(c)))
                    return false;
                val = val * 10 + (c - '0');
            }
            if (val > 255)
                return false;
        }
        return fields == 4;  // catches the trailing '.' that getline swallowed
    }

    bool validIpv6(const string& ip) {
        if (count(ip.begin(), ip.end(), ':') != 7)
            return false;  // framing: exactly 7 colons

        istringstream ss(ip);
        string comp;
        int fields = 0;
        while (getline(ss, comp, ':')) {
            ++fields;
            if (comp.empty() || comp.size() > 4)
                return false;  // empty ("::" not allowed) or too long
            for (char c : comp) {
                if (!isxdigit(static_cast<unsigned char>(c)))
                    return false;
            }
        }
        return fields == 8;  // catches the trailing ':' that getline swallowed
    }
};

int main() {
    Solution sol;
    assert(sol.validIPAddress("172.16.254.1") == "IPv4");
    assert(sol.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334") == "IPv6");
    assert(sol.validIPAddress("256.256.256.256") == "Neither");
    assert(sol.validIPAddress("192.168.01.1") == "Neither");  // leading zero
    assert(sol.validIPAddress("1.1.1.1.") == "Neither");      // trailing delimiter
    assert(sol.validIPAddress("1..1.1") == "Neither");        // empty field
    assert(sol.validIPAddress("2001:db8::1") == "Neither");   // no :: compression
    assert(sol.validIPAddress("2001:0db8:85a3::8A2E:037j:7334") == "Neither");
    return 0;
}
