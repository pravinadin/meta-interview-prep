# Error log

Add a row for every problem, drill or mock moment that went wrong, newest first. Each Saturday, group rows by Pattern; the top 2 patterns get next week's redo slots.

| Date | Problem / round | Pattern | What went wrong | Redo on | Fixed? |
| --- | --- | --- | --- | --- | --- |
| Nov 3 | LC 468 | String parsing | Trusted `getline`: it swallows a trailing delimiter (`"1.1.1.1."` passed) and empty tokens skipped every check (`"1..1.1"` passed). Fix: count delimiters first, reject empty fields, check field count == 4 / 8 | Nov 4 | |
| Nov 3 | LC 71 (C version) | Strings / C memory | `char* stack[1000]` overflows (3000-char path has up to 1500 components); `strcat` in a loop is O(n²). Fix: size from `strlen/2+1`, write pointer + `memcpy` | Nov 4 | |
| Nov 3 | LC 227 | Stack / expression parsing | Assumed `* > / > + > -` (really 2 levels, left to right); needed hints on applying the pending op only when a number completes and on flushing the last number (sentinel at `i == n`). O(1) version not derived alone. Test for negative division must be inexact: `"3-5/2"` = 1 | Nov 4 | |
| (example) Nov 2 | LC 76 | Sliding window | Shrank the window before the counts matched; 40 min | Nov 3 | |
| | | | | | |
