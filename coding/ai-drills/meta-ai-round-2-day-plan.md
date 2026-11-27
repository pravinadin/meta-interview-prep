# 2-Day Meta Coding Interview Plan

Nov 27, 2026

Two 8-hour days built from the Meta AI-round questions reported on PracHub. Day 1 covers every non-maze question type, and Day 2 covers the maze family (the most reported) plus three 60-minute mocks in the reported phases.

## Where you stand

Meta's AI-enabled round is 60 minutes in CoderPad with an AI chat built in. It runs in three phases: fix a bug in a multi-file codebase, implement the core algorithm, then extend or optimize it when a new rule or bigger input breaks it. Interviewers score problem solving, code quality, verification and communication ([PracHub](https://prachub.com/resources/meta-ai-coding-interview)). Your Alphabet Words session was a full rehearsal of exactly this shape, and "maximum unique characters" is on the known problem list.

| Area | What the session showed | Fix in this plan |
| --- | --- | --- |
| Approach | You reached subsets-with-no-shared-letters quickly and wrote a working DFS that passed | Keep: say it in 1 sentence first, then pseudocode |
| Debugging (phase 1) | The `frequencyMap['a']` insert took several rounds; you changed the expected value to 11 | Day 1 block 6: planted-bug drills using the 5-step detective method |
| Optimization (phase 3) | First version stored every valid subset: O(S·m·L) space | Every mock: brute force first, then optimize (bitmask, trie, state BFS) and benchmark |
| Spec reading | Several subsets reach 12, so the test's tie-break (input order, strict `>`) decides the answer | Each mock: write down the tie-break and output order before coding |
| Complexity | Needed help counting how many subsets are stored | Every problem: state time/space out loud before running |

The goal is not more problems. It is 11 templates you can write cold in under 10 minutes each, plus a script for phases 1 and 3.

## Day 1: Meta's non-maze AI-round questions (8 h)

Day 1 covers unique characters, three cards summing to 15, suffix queries, alien alphabet order, friend recommendations, the expiring record store and the card deck. Each block ends with the reported phase-3 move: a benchmark, a tie-break or a new rule.

| Time | Block | Do | Done when |
| --- | --- | --- | --- |
| 0:00–1:00 | 1. Unique characters | Re-solve Alphabet Words cold in 45 min, then the length-only version (≤ 16 words, LC 1239) in 10 | Both pass; complexity stated |
| 1:00–2:00 | 2. Cards summing to 15 | Indices of 3 distinct cards summing to 15, lexicographically smallest, n ≤ 2000: have the AI write the O(n³) brute force, then write O(n²) with a value → first-index map yourself (LC 15 pattern). Then LC 464 for the strategy-game follow-up | Yours matches the brute force on 200 random cases |
| 2:00–3:30 | 3. Suffix queries and tries | LC 208, then LC 3093: reverse the words, and store the best index at every trie node (shorter word, then smaller index). Benchmark against brute force at 10^5 words. Then LC 472 | Trie beats brute force by 10× or more; both tie-breaks tested |
| 3:30–3:45 | Break | Away from the screen | |
| 3:45–4:45 | 4. Ordering graphs | LC 269: constraints from adjacent words, Kahn's topological sort, "" for a cycle or "abc" before "ab". Then the lexicographically smallest order with a min-heap. LC 1311 for friend recommendations | Cycle and prefix cases return "" |
| 4:45–6:15 | 5. Build-a-library tasks | Expiring record store in C++: set/get/delete → sorted scan and prefix scan → TTL with lazy expiry. Card deck: reset, Fisher–Yates shuffle (LC 384), draw(n), remaining. Decide what draw(n) does when cards run short, and write gtests | All 3 store parts pass your tests; deck tests cover the short draw |
| 6:15–7:15 | 6. Debugging drills (phase 1) | Plant 3 bugs in today's code: a `map[]` insert in a test, an off-by-one `<=`, a CRLF `\r` in the input. Debug each out loud with the detective method | Each found in ≤ 5 min |
| 7:15–8:00 | 7. Review | Re-solve the day's weakest problem without notes. Write the trie and topological-sort templates on paper | Both from memory |

## Day 2: The maze family and three full mocks (8 h)

Mazes are the most reported Meta AI-round question, so Day 2 opens with every maze variant on PracHub. It then runs three 60-minute mocks rebuilt from the reported phases.

| Time | Block | Do | Done when |
| --- | --- | --- | --- |
| 0:00–0:30 | Warm-up | Write the bitmask-subset, BFS-with-state, trie and topological-sort templates from memory | 4/4 written |
| 0:30–2:00 | 1. Maze variants | LC 1091 (add path printing with `parent`), 864 (keys and doors: state (r, c, keyMask), ≤ 6 keys), then the rolling ball: 490, 505, 499 (stop cells, Dijkstra, lexicographically smallest path). Talk through teleporters and a fuel limit as extra state | Each extension added in ≤ 10 lines |
| 2:00–3:00 | 2. Mock 1: Extend a Maze Solver | 60 min in the reported phases: fix the failing traversal tests → min moves S→T or -1 → a movement rule (e.g. no reversing the last move, so the state adds lastDir) → keys and doors | Phase 4 working by minute 55 |
| 3:00–3:30 | Debrief + break | Write 3 things that cost time and 1 fix each | List written |
| 3:30–4:30 | 3. Mock 2: Maze + suffix queries | Part 1: keys-and-doors maze, 100×100, ≤ 6 keys. Part 2: suffix queries with both tie-breaks: brute force, then the trie, then a benchmark | Benchmark numbers stated out loud |
| 4:30–5:30 | 4. Mock 3: Expiring record store | All 3 parts in 60 min, with the AI writing the operation-list test harness | TTL correct at the boundary t = timestamp + ttl |
| 5:30–5:45 | Break | Away from the screen | |
| 5:45–7:15 | 5. Classic-round set | 6 of: LC 1249, 408, 567, 986, 1650, 199, 129, 339, 498, 65, 121, at 12 min each. These come from the same Meta loops | 5 of 6 inside time |
| 7:15–8:00 | 6. Final review | Playbook, tie-break checklist, all templates on paper | All from memory |

## Problem list: 28 problems, grouped by the Meta question they prepare

Each row is the closest LeetCode drill for a reported Meta question. Solve them in order, type your time in the last column, and redo anything over target the next morning. Problems marked Premium need LeetCode Premium; for those, use the free PracHub write-up instead.

| Day | Meta question | Problem | Level | Template | Target | Your time |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | Unique characters | [1239. Max Length of a Concatenated String with Unique Characters](https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/) | Medium | T3 | 10 min | |
| 1 | Cards summing to 15 | [15. 3Sum](https://leetcode.com/problems/3sum/) | Medium | T5 | 15 min | |
| 1 | Fifteen-sum card strategy | [464. Can I Win](https://leetcode.com/problems/can-i-win/) | Medium | T4 | 25 min | |
| 1 | Fifteen-sum card strategy | [1275. Find Winner on a Tic Tac Toe Game](https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/) | Easy | T4 | 10 min | |
| 1 | Suffix queries | [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) | Medium | T8 | 15 min | |
| 1 | Suffix queries | [3093. Longest Common Suffix Queries](https://leetcode.com/problems/longest-common-suffix-queries/) | Hard | T8 | 30 min | |
| 1 | Words containing other words | [472. Concatenated Words](https://leetcode.com/problems/concatenated-words/) | Hard | T8 | 30 min | |
| 1 | Unknown alphabet order | [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) (Premium) | Hard | T9 | 25 min | |
| 1 | Friend recommendations | [1311. Get Watched Videos by Your Friends](https://leetcode.com/problems/get-watched-videos-by-your-friends/) | Medium | T7 | 20 min | |
| 1 | Card deck | [384. Shuffle an Array](https://leetcode.com/problems/shuffle-an-array/) | Medium | T11 | 10 min | |
| 1 | Expiring record store | [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/) | Medium | T11 | 20 min | |
| 2 | Maze solver | [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/) | Medium | T6 | 15 min | |
| 2 | Maze with keys and doors | [864. Shortest Path to Get All Keys](https://leetcode.com/problems/shortest-path-to-get-all-keys/) | Hard | T6 | 30 min | |
| 2 | Maze with extra state | [1293. Shortest Path in a Grid with Obstacles Elimination](https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/) | Hard | T6 | 25 min | |
| 2 | Rolling-ball maze | [490. The Maze](https://leetcode.com/problems/the-maze/) (Premium) | Medium | T6 | 15 min | |
| 2 | Rolling-ball maze | [505. The Maze II](https://leetcode.com/problems/the-maze-ii/) (Premium) | Medium | T10 | 20 min | |
| 2 | Rolling-ball maze | [499. The Maze III](https://leetcode.com/problems/the-maze-iii/) (Premium) | Hard | T10 | 30 min | |
| 2 | Classic round | [1249. Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/) | Medium | Stack | 12 min | |
| 2 | Classic round | [408. Valid Word Abbreviation](https://leetcode.com/problems/valid-word-abbreviation/) (Premium) | Easy | Two pointers | 10 min | |
| 2 | Classic round | [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/) | Medium | Sliding window | 12 min | |
| 2 | Classic round | [986. Interval List Intersections](https://leetcode.com/problems/interval-list-intersections/) | Medium | Two pointers | 12 min | |
| 2 | Classic round | [1650. Lowest Common Ancestor of a Binary Tree III](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/) (Premium) | Medium | Parent pointers | 10 min | |
| 2 | Classic round | [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) | Medium | BFS levels | 10 min | |
| 2 | Classic round | [129. Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/) | Medium | DFS | 10 min | |
| 2 | Classic round | [339. Nested List Weight Sum](https://leetcode.com/problems/nested-list-weight-sum/) (Premium) | Medium | DFS | 10 min | |
| 2 | Classic round | [498. Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/) | Medium | Bucketing | 15 min | |
| 2 | Classic round | [65. Valid Number](https://leetcode.com/problems/valid-number/) | Hard | State machine | 20 min | |
| 2 | Classic round | [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | Easy | Running min | 5 min | |

## Meta AI-round question bank: what's actually asked

PracHub's free Meta write-ups show 8 question types. Nearly all of them hinge on an exact tie-break rule, a brute force to benchmark against, or a later phase that adds one rule to the same state.

| Question | What's asked (phases as reported) | Core technique | Template |
| --- | --- | --- | --- |
| [Extend a Maze Solver](https://prachub.com/interview-questions/extend-a-maze-solver-2) | Fix the failing traversal tests → min moves S→T or -1 → movement restrictions → keys and doors | BFS; the state grows from (r, c) to (r, c, keys) | T6 |
| [Maze + suffix queries](https://prachub.com/coding-questions/solve-maze-and-suffix-problems) | (1) Keys-and-doors maze, 100×100, ≤ 6 keys. (2) For each query, the word with the longest common suffix; ties go to the shorter word, then the smaller index; 10^5 words; benchmark against brute force | BFS over (cell, keyMask); a reversed-word trie storing the best index at each node | T6, T8 |
| [Rolling-ball maze set](https://prachub.com/coding-questions/solve-matrix-tree-nested-lca-maze-tasks) | Can the ball stop at the target → min distance → lexicographically smallest shortest path to a hole → 10^4 queries on one maze | Search over stop cells; Dijkstra on (dist, path); cache results per start | T10 |
| [Unique characters](https://prachub.com/coding-questions/maximize-unique-characters-from-words) (4 versions) | Max total length of words sharing no letters; ≤ 16 words; sometimes return the subset | Masks + backtracking + pruning | T3 |
| [Three cards summing to 15](https://prachub.com/coding-questions/solve-two-backtracking-array-problems) | Indices of 3 distinct cards summing to 15, lexicographically smallest; n ≤ 2000, values up to ±10^9. A locked follow-up optimizes a fifteen-sum card strategy | O(n²) with a value → first-index map, scanning left to right; the game is minimax over a used-cards mask | T5, T4 |
| [Infer an unknown alphabet order](https://prachub.com/coding-questions/infer-an-unknown-alphabet-order) | Letter order from sorted words; "" for a cycle or a word before its own prefix; version 2 wants the lexicographically smallest order | Constraints from adjacent words + Kahn's algorithm; a min-heap for version 2 | T9 |
| [Expiring record store](https://prachub.com/coding-questions/implement-an-expiring-record-store) | set/get/delete → sorted scan and prefix scan → timestamps with TTL (visible while timestamp ≤ t < timestamp + ttl); 2×10^5 operations | `unordered_map<key, map<field, Entry{value, expiresAt}>>` with lazy expiry | T11 |
| [Card deck library](https://prachub.com/interview-questions/solve-parser-trading-tree-and-deck-tasks) | reset, shuffle, draw(n), remaining; you define draw(n) when cards run short; unit tests | Enums + a vector + a draw index; Fisher–Yates shuffle | T11 |

These are locked, but their titles show the template: [friend recommender](https://prachub.com/coding-questions/build-a-friend-recommender) (T7), [words containing other words](https://prachub.com/coding-questions/find-words-containing-other-words) (T8), [key-door corridor maze](https://prachub.com/coding-questions/solve-a-key-door-corridor-maze) (T6). The [FastAPI summarization service](https://prachub.com/interview-questions/build-a-fastapi-summarization-service) is a Python layering exercise, so it's low priority for a C++ interview.

**Three habits these questions reward:**

1. Write the tie-break rule down before coding: lexicographically smallest triple, path or order; shorter word, then smaller index.
2. Build the brute force first (the AI can write it), then optimize and benchmark against it.
3. Decide unspecified behaviour out loud and test it: draw(n) when cards run short, a TTL exactly at its boundary, a word that comes before its own prefix.

## Interview-day playbook

Run the same script every round, so your head stays on the problem rather than the process.

**Phase 1: Fix the bug (detective method)**

1. Read the failure literally: the file and line, the expression, actual vs. expected.
2. Size the gap: off by one, wrong order, or empty? Each points to a kind of bug.
3. Use the passing tests as alibis: they clear code that's already working.
4. Read the lines before the failure: what changed the state? (`map[]` inserts, `getline` leaves a `\r`, a `<=` runs one past the end.)
5. Print to confirm, then fix the cause. Never edit an expected value to match the current output.

**Phase 2: Core implementation**

1. Clarify: input size, alphabet, invalid inputs, output format, and **the tie-break when there are several right answers**.
2. Say the approach in one sentence and name its template (T1–T11).
3. Write pseudocode in a comment, then state time and space before you code.
4. Use the AI for boilerplate, parsing and test harnesses, with specific prompts that name the algorithm. Read every line it writes, and keep talking while it works.
5. Run often: small cases first, then the given data.

**Phase 3: Extend or optimize**

1. Ask what broke: the new rule, or the input size.
2. Use the improvement ladder: store everything → running best → bitmask or extra state → prune or memoize.
3. Re-state the new complexity and how it compares to the old.

**Lines to say out loud**

- "Several subsets are optimal, so the order is part of the spec. I'll keep the first one with a strict `>`."
- "My first version is O(S·m·L) space. I only need the max, so I'll keep a running best and bring it to O(W)."
- "`operator[]` on `std::map` inserts. I'll read with `count` or `find`."

**Checklist before you say "done"**

- [ ] Edge cases tested: empty input, a single item, duplicates, invalid words
- [ ] Complexity stated for the final version
- [ ] Output order and tie-break match the spec
- [ ] No `[]` reads on maps in const contexts or tests

## Memory hooks cheat sheet

One picture and one line of code per template. Read this the night before and the morning of the interview.

| Template | Hook | Core line to remember |
| --- | --- | --- |
| T1 Subsets | Suitcase: take the item or skip it | `take(i+1); pop; skip(i+1);` |
| T2 Permute / grid | Musical chairs: sit, play on, stand up | `used[i]=1; dfs(); used[i]=0;` |
| T3 Bitmask DFS + bound | Tetris board: pieces can't overlap | `if (!(m & used)) dfs(used \| m); if (score + reach <= best) return;` |
| T4 Bitmask DP / games | Light switches: the mask is the whole room's state | `dp[mask \| w] = best(dp[mask] + gain)`; game: "I win if any move leaves you losing" |
| T5 Hash maps + tie-breaks | Hotel clerk: asking about room 'a' builds it | Write with `[]`, read with `count`/`find`/`at`; keep the first index seen for the smallest answer |
| T6 Grid BFS + state | Ripples in a pond; keys add a layer of rooms | `visited[r][c][keyMask]`; `parent` map for the path |
| T7 Graph BFS + count | Party: friends of friends, ranked by mutuals | Level-by-level BFS, count at level 2, sort by (count desc, id asc) |
| T8 Trie / word DP | Phone keypad autocomplete | `node->next[c]`; store the best index at every node for queries |
| T9 Topological sort | Recipe steps: you can't frost before you bake | Indegree-0 letters in a queue (min-heap for the smallest order); output shorter than K means a cycle |
| T10 Dijkstra on stop cells | Bowling ball: it only stops at walls | Priority queue of (dist, path); the edge weight is the roll length |
| T11 Store / library design | Filing cabinet with expiry stickers | `map` per key for sorted scans; keep `expiresAt`; drop an entry on read when t ≥ expiresAt |

## Meta questions from AI-assisted rounds (PracHub)

Mazes dominate: 8 of the 23 Meta coding questions in PracHub's AI-assisted list are maze variants, plus 2 more on its Meta page. That makes T6 (BFS + state) your highest-value template. 11 of the 23 are free to read. Do the free ones in Day 2's mocks before deciding whether to pay for the rest.

| Theme | Question | Level | Free | Template |
| --- | --- | --- | --- | --- |
| Maze | [Extend a Maze Solver](https://prachub.com/interview-questions/extend-a-maze-solver-2) | Medium | Yes | T6 |
| Maze | [Solve Maze and Suffix Problems](https://prachub.com/coding-questions/solve-maze-and-suffix-problems) | Medium | Yes | T6, T8 |
| Maze | [Solve Matrix, Tree, Nested, LCA, Maze Tasks](https://prachub.com/coding-questions/solve-matrix-tree-nested-lca-maze-tasks) | Medium | Yes | T6 |
| Maze | [Extend a Maze Solver](https://prachub.com/interview-questions/extend-a-maze-solver) | Hard | No | T6 |
| Maze | [Extend a Maze Solver](https://prachub.com/interview-questions/extend-a-maze-solver-3) | Medium | No | T6 |
| Maze | [Solve a Key-Door Corridor Maze](https://prachub.com/coding-questions/solve-a-key-door-corridor-maze) | Medium | No | T6 + key mask |
| Maze | [Solve Tree Columns And Maze Variants](https://prachub.com/coding-questions/solve-tree-columns-and-maze-variants) | Medium | No | T6 |
| Maze | [Solve array, tree, and maze problems](https://prachub.com/coding-questions/solve-array-tree-and-maze-problems) | Medium | No | T6 |
| Maze | [Find the shortest path through a maze with keys, doors and teleporters](https://prachub.com/interview-questions/find-the-shortest-path-through-a-maze-with-keys-doors-and-teleporters) | Hard | ? | T6 + key mask |
| Maze | [Find the fewest steps through a maze with teleporters and a fuel limit](https://prachub.com/interview-questions/find-the-fewest-steps-through-a-maze-with-teleporters-and-a-fuel-limit) | Medium | ? | T6 + fuel state |
| Unique characters | [Maximize Unique Characters from Words](https://prachub.com/coding-questions/maximize-unique-characters-from-words) | Medium | Yes | T3 |
| Unique characters | [Maximum Length of a Word Selection With All Unique Characters](https://prachub.com/coding-questions/maximum-length-of-a-word-selection-with-all-unique-characters) | Medium | Yes | T3 |
| Unique characters | [Maximum Character Coverage From Words With No Shared Letters](https://prachub.com/coding-questions/maximum-character-coverage-from-words-with-no-shared-letters) | Medium | ? | T3 |
| Unique characters | [Find Maximum Unique-Character Subset](https://prachub.com/interview-questions/find-maximum-unique-character-subset) | Hard | No | T3 |
| Friend recommendations | [Build a Friend Recommender](https://prachub.com/coding-questions/build-a-friend-recommender) | Hard | No | T7 |
| Friend recommendations | [Build Friend Recommendations](https://prachub.com/interview-questions/build-friend-recommendations) | Medium | No | T7 |
| Sum-to-15 game | [Optimize a Fifteen-Sum Card Strategy](https://prachub.com/coding-questions/optimize-a-fifteen-sum-card-strategy) | Hard | No | T4 |
| Words in words | [Find Words Containing Other Words](https://prachub.com/coding-questions/find-words-containing-other-words) | Hard | No | T8 |
| Other coding | [Infer an Unknown Alphabet Order](https://prachub.com/coding-questions/infer-an-unknown-alphabet-order) | Medium | Yes | T9 |
| Other coding | [Solve Two Backtracking Array Problems](https://prachub.com/coding-questions/solve-two-backtracking-array-problems) | Hard | Yes | T1, T2 |
| Other coding | [Implement an Expiring Record Store](https://prachub.com/coding-questions/implement-an-expiring-record-store) | Medium | Yes | T11 |
| Other coding | [Solve Parser, Trading, Tree, and Deck Tasks](https://prachub.com/interview-questions/solve-parser-trading-tree-and-deck-tasks) | Medium | Yes | Mixed |
| Other coding | [Solve Three Coding Interview Problems](https://prachub.com/interview-questions/solve-three-coding-interview-problems-3) | Medium | Yes | Mixed |
| Other coding | [Build a FastAPI summarization service](https://prachub.com/interview-questions/build-a-fastapi-summarization-service) | Medium | Yes | Python service |
| Other coding | [Implement Sparse Matrix Operations](https://prachub.com/interview-questions/implement-sparse-matrix-operations) | Medium | No | Hash map |
| Other coding | [Solve coding and AI-assisted tasks](https://prachub.com/coding-questions/solve-coding-and-ai-assisted-tasks) | Medium | No | Grids, linked lists |
| Other coding | [Schedule Multi-Step Dish Recipes Across Three Chefs](https://prachub.com/interview-questions/schedule-multi-step-dish-recipes-across-three-chefs-to-finish-an-order-fastest) | Medium | ? | Greedy scheduling |

Design and ML items in the same list, for other rounds: [Design an On-Demand Delivery Platform](https://prachub.com/interview-questions/design-an-on-demand-delivery-platform), [Design an Online Judge and Live Comments](https://prachub.com/interview-questions/design-an-online-judge-and-live-comments), [Design a Code Review Agent](https://prachub.com/interview-questions/design-a-code-review-agent), [Derive Linear Regression Solution](https://prachub.com/interview-questions/derive-linear-regression-solution).

Compiled from [prachub.com/ai-assisted](https://prachub.com/ai-assisted) (all 6 pages) and [prachub.com/companies/meta](https://prachub.com/companies/meta). "?" means the question came from the Meta page, which doesn't show whether it's locked. The listing re-sorts between pages, so a few of its 104 questions may have been missed.

## Meta SWE hot list: classic coding round

The classic round's hot questions are mostly reworded LeetCode problems, so practise the LeetCode version. 1249, 408, 567 and 986, plus LCA (as 1650), are already in Day 2's classic-round set; 691 is extra bitmask-DP practice for T4.

| Topic | PracHub question | Likely LeetCode equivalent | Level |
| --- | --- | --- | --- |
| Stack / greedy | [Remove the Fewest Parentheses to Restore Validity](https://prachub.com/interview-questions/remove-the-fewest-parentheses-to-restore-validity) | [1249. Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/) | Medium |
| Two pointers | [Check whether a compressed string with numeric skips matches the expanded string](https://prachub.com/interview-questions/check-whether-a-compressed-string-with-numeric-skips-matches-the-expanded-string) | [408. Valid Word Abbreviation](https://leetcode.com/problems/valid-word-abbreviation/) | Easy |
| Sliding window | [Detect a Permuted Pattern in a Contiguous Window](https://prachub.com/interview-questions/detect-a-permuted-pattern-in-a-contiguous-window) | [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/) | Medium |
| Intervals | [Intersect Two Sorted Lists of Disjoint Closed Intervals](https://prachub.com/interview-questions/intersect-two-sorted-lists-of-disjoint-closed-intervals) | [986. Interval List Intersections](https://leetcode.com/problems/interval-list-intersections/) | Medium |
| Trees | [Lowest Common Ancestor of Two Values in a Binary Tree Given in Level Order](https://prachub.com/coding-questions/lowest-common-ancestor-of-two-values-in-a-binary-tree-given-in-level-order) | [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) | Medium |
| Bitmask DP | [Find the fewest reusable word stickers needed to spell a target string](https://prachub.com/interview-questions/find-the-fewest-reusable-word-stickers-needed-to-spell-a-target-string) | [691. Stickers to Spell Word](https://leetcode.com/problems/stickers-to-spell-word/) | Hard |
| Grid BFS | [Shortest 8-Directional Clear Path Across a Binary Grid](https://prachub.com/coding-questions/shortest-8-directional-clear-path-across-a-binary-grid) | [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/) (already on Day 2) | Easy |
| Backtracking | [Enumerate Distinct Subsets with Repeated Input Values](https://prachub.com/interview-questions/enumerate-distinct-subsets-with-repeated-input-values) | [90. Subsets II](https://leetcode.com/problems/subsets-ii/) | Medium |
| Trees | [Find the value in a binary search tree that is closest to a target](https://prachub.com/interview-questions/find-the-value-in-a-binary-search-tree-that-is-closest-to-a-target) | [270. Closest Binary Search Tree Value](https://leetcode.com/problems/closest-binary-search-tree-value/) | Easy |
| Trees | [Sum the Values of a BST That Fall Within an Inclusive Range](https://prachub.com/coding-questions/sum-the-values-of-a-binary-search-tree-that-fall-within-an-inclusive-range) | [938. Range Sum of BST](https://leetcode.com/problems/range-sum-of-bst/) | Easy |
| Arrays | [Check whether an integer array is monotonic](https://prachub.com/interview-questions/check-whether-an-integer-array-is-monotonic-entirely-non-decreasing-or-non-increasing) | [896. Monotonic Array](https://leetcode.com/problems/monotonic-array/) | Easy |
| DP | [Minimize the Number of Perfect Squares Summing to an Integer](https://prachub.com/interview-questions/minimize-the-number-of-perfect-squares-summing-to-an-integer) | [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/) | Medium |
| DP / trees | [Count BST Shapes with Exact Catalan Arithmetic](https://prachub.com/interview-questions/count-bst-shapes-with-exact-catalan-arithmetic) | [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/) | Medium |
| Sorting | [Find the Largest Sorted-Neighbor Gap in Linear Time](https://prachub.com/interview-questions/find-the-largest-sorted-neighbor-gap-in-linear-time) | [164. Maximum Gap](https://leetcode.com/problems/maximum-gap/) | Medium |
| Linked lists | [Delete a Non-Tail Value through Its Supplied Node](https://prachub.com/interview-questions/delete-a-non-tail-value-through-its-supplied-node) | [237. Delete Node in a Linked List](https://leetcode.com/problems/delete-node-in-a-linked-list/) | Medium |
| Games | [Decide the Winner of One-to-Three Stone Nim](https://prachub.com/interview-questions/decide-the-winner-of-one-to-three-stone-nim) | [292. Nim Game](https://leetcode.com/problems/nim-game/) | Easy |
| Binary search | [Count Complete Rows in a Coin Staircase](https://prachub.com/interview-questions/count-complete-rows-in-a-coin-staircase) | [441. Arranging Coins](https://leetcode.com/problems/arranging-coins/) | Easy |
| Graphs | [Implement friend recommendations (people you may know) for a social graph](https://prachub.com/interview-questions/implement-friend-recommendations-people-you-may-know-for-a-social-graph) | Like [1311](https://leetcode.com/problems/get-watched-videos-by-your-friends/) (T7) | Medium |
| Mixed | [Range sums, closed-interval overlap counts and grid shortest path in one function](https://prachub.com/interview-questions/range-sums-closed-interval-overlap-counts-and-grid-shortest-path-in-one-function) | Prefix sums + line sweep + BFS | Medium |
| Arrays | [Find the best value-for-money item within a budget](https://prachub.com/interview-questions/find-the-best-value-for-money-item-within-a-budget) | No direct equivalent: a linear scan with a tie-break | Easy |

Compiled from pages 1–2 of [Meta SWE, sorted by hot](https://prachub.com/companies/meta/positions/software-engineer?sort=hot) (pages 3 onward of that view repeat page 1). The LeetCode mappings are my matches from the titles, so check each one when you open it. The [coding category](https://prachub.com/companies/meta/positions/software-engineer/categories/coding-and-algorithms) has 49 more pages, mostly older LeetCode rewordings.

## Sources

- [Meta's AI-Enabled Coding Interview: What to Expect in 2026 (PracHub)](https://prachub.com/resources/meta-ai-coding-interview)
- Alphabet Words session notes: `Coding/alphabet-words.md` in [InterviewPrep](https://github.com/pravinadin/InterviewPrep)
- PracHub Meta question write-ups, linked in the question bank and lists above
