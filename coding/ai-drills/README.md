# Multi-part AI drills

Each drill mimics the AI-enabled coding round: a small C++ codebase (3–5 files plus a test file) with 2 planted bugs. In practice only, have an AI generate the project without telling you where the bugs are. Then work it in 60 min (drill #1: 90 min). Put each drill in its own folder, e.g. `01-route-table/`, with a `NOTES.md` covering what the AI got wrong and how you caught it.

| # | Date | Theme | Part 1: fix | Part 2: extend | Part 3: scale / contract change | Done |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | Sat Nov 7 | Route table | Broken prefix parsing | Longest-prefix match via binary trie | ECMP next-hop sets; route withdraw with ref counts | [ ] |
| 2 | Sun Nov 8 | KV store | Wrong overwrite semantics | TTL expiry | Nested transactions: begin / commit / rollback | [ ] |
| 3 | Wed Nov 11 | Log analyzer | Parser drops malformed lines | Top-K error codes per window | EWMA-based alerting; streaming input that doesn't fit in memory | [ ] |
| 4 | Sun Nov 15 | Task scheduler | Cycle not detected | Topological order | Minimum total time with N parallel workers | [ ] |
| 5 | Tue Nov 17 | Spreadsheet | Off-by-one cell refs | Formula evaluation with dependencies | Incremental recompute on change; cycle errors | [ ] |

## Using the AI in the room

1. Read the codebase and tests first (5 min). Run the tests to see the baseline before prompting anything.
2. State your plan out loud, then give the AI bounded tasks: boilerplate, a test case list, syntax you forgot, explaining an unfamiliar file.
3. Ask it to explain its approach before it writes code. Reject approaches that don't match your plan, and say why.
4. Review every line it produces, including its complexity claims; catching a wrong one aloud is a positive signal.
5. Run the tests after every change. Add your own edge cases (empty input, duplicates, overflow, huge input).
6. Never paste the whole problem and accept the answer.
