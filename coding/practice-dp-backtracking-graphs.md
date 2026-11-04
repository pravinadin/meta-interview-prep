# Practice ladder: backtracking, DP, state-space graphs, game search

Goal: solve these by *recognizing the shape*, not by recalling the answer. Each ladder goes from the plainest form of a pattern to the version Meta actually tests. Problems already in the main schedule are marked ⓢ.

## 1. What Meta actually asks (analysis, Nov 4)

Candidate reports, not official Meta statements. Small sample; the pool may rotate.

**AI-enabled round: harder than a medium, but not exotic.** It is one multi-stage task (fix bugs → implement → scale/optimize) in a small multi-file codebase, often 120+ lines. Reported themes:

| Reported problem | Algorithm underneath | Ladder below |
| --- | --- | --- |
| Maze solver with path printing; gates, keys and doors, portals, bombs | BFS with parent pointers; BFS over **(cell, extra state)** | §4: 1091, 864, 1293, 490 |
| Maximize unique characters across a word list | Backtracking + bitmask pruning (≈ LC 1239) | §2: 78, 1239, 698 |
| Find a subset of words with a property; words containing other words | Exhaustive search + pruning, tries | §2: 212, 472 |
| Card game: grid of cards, pick 3 summing to 15; strategy scored over many games | Combination search; backtracking or DP beats greedy; Monte Carlo evaluation | §2, §3, §5 |
| Friend recommendations on a large graph | 2-hop BFS + counting + top-K heap | §4 + existing heap set |

What makes it hard is **volume and the scale-up stage**, not rare algorithms. Not one report mentions minimax, A* or MCTS.

**Classic rounds: mostly mediums, sometimes a hard, two in ~45 min.** DP is rare and basic there. Speed and an optimal (not brute-force) answer decide it.

**So the priorities are:**
1. Backtracking with pruning and bitmasks, and BFS over state: these map directly to the reported pool.
2. DP as *memoized backtracking*: the optimization step in stage 3/4, and an occasional classic question.
3. A*: cheap to learn once BFS/Dijkstra are solid, and a strong "how would you scale this maze?" answer.
4. Minimax: light. Know the score-difference recursion.
5. MCTS: concept only. Monte Carlo *evaluation* (simulate many games) is the part that showed up.

Sources: [Hello Interview](https://www.hellointerview.com/blog/meta-ai-enabled-coding) · [PracHub](https://prachub.com/resources/meta-ai-coding-interview) · [aicodinginterview.com reports](https://aicodinginterview.com/interviews/meta/) · [TechScreen](https://techscreen.app/articles/meta-technical-interview-process-2026)

## Recognize the shape first

| The question asks… | Shape | First move |
| --- | --- | --- |
| "List / count every valid arrangement", constraints to satisfy | Backtracking | Write choose → explore → un-choose |
| "Min / max / number of ways", and the same sub-question repeats | DP | Write the backtracking, then memoize it |
| "Fewest steps", unweighted moves | BFS | What is a *state*? Only the cell, or cell + keys? |
| "Cheapest path", weighted moves | Dijkstra | Lazy deletion: skip stale heap entries |
| Shortest path and you know roughly where the goal is | A* | Dijkstra + admissible heuristic |
| Two players, both play optimally | Minimax | Score difference: `best = max(gain − best(next))` |
| Huge game tree, no good heuristic | MCTS | Concept answer only |

## 2. Backtracking ladder

**Mental model: a config transaction.** Apply a change, run the test, roll it back, try the next one. Every bug in backtracking is a missing rollback.

**Hook: choose → explore → un-choose.**

| # | Problem | New idea at this rung | Tier |
| --- | --- | --- | --- |
| 78 | Subsets ⓢ | Include / exclude: the base tree | 1 |
| 90 | Subsets II | Sort, then skip equal siblings at the same depth | 1 |
| 46 | Permutations ⓢ | `used[]` instead of a start index | 1 |
| 39 | Combination Sum | Reuse allowed (recurse with `i`, not `i+1`); sort to prune early | 1 |
| 22 | Generate Parentheses | Choices driven by constraints (open < n, close < open) | 1 |
| 131 | Palindrome Partitioning | Choose a *cut position*, not an element | 1 |
| 79 | Word Search | Grid: mark the cell on entry, unmark on exit | 1 |
| 51 | N-Queens | Constraint sets (columns, diagonals `r−c`, `r+c`) for O(1) checks | 1 |
| 1239 | Max Length of Concatenated String with Unique Characters ⓢ | Bitmask state; prune words with internal duplicates. **Reported AI-round theme** | 1 |
| 698 | Partition to K Equal Sum Subsets | Bucket filling; sort descending; skip symmetric empty buckets | 2 |
| 212 | Word Search II | Trie prunes the whole search. Words-in-words theme | 2 |
| 301 | Remove Invalid Parentheses | Meta hard; count minimum removals first, then prune | 2 |
| 282 | Expression Add Operators | Meta hard; carry the last operand for `*` (like 227's "last line") | 2 |
| 472 | Concatenated Words | Words containing other words; trie or word-break DP | 2 |

```cpp
void bt(int start, vector<int>& path) {
    record(path);                        // or: if (goal(path)) { save; return; }
    for (int i = start; i < n; ++i) {
        if (prune(i)) continue;          // skip duplicates / impossible branches
        path.push_back(nums[i]);         // choose
        bt(i + 1, path);                 // explore (i, not i+1, if reuse is allowed)
        path.pop_back();                 // un-choose (the rollback)
    }
}
```

**You have it when:** for an unseen problem you can say, before coding, (1) what a choice is, (2) what the rollback undoes, and (3) one pruning rule.

## 3. DP ladder

**Mental model: distance-vector routing.** A router's distance to a destination is `min over neighbors (link cost + neighbor's distance)`. That is a DP transition, and Bellman-Ford is DP. The table is the routing table: each entry is computed once and reused by everyone who asks.

**Hook: DP is backtracking that remembers.** For every problem below: write the brute-force recursion, add a memo, and only then (if asked) turn it into a table.

**The five questions, answered before any code:**
1. **State:** what is the smallest description of "where I am"? (index, remaining capacity, bitmask…)
2. **Choice:** what can I do from here?
3. **Transition:** how does the answer for this state come from smaller states?
4. **Base case:** where does recursion stop?
5. **Order:** for a table, which states must be filled first?

| # | Problem | New idea at this rung | Tier |
| --- | --- | --- | --- |
| 70 → 198 | Climbing Stairs → House Robber | 1D, two choices; then "take it or skip it" (15 min for both) | 1 |
| 322 | Coin Change | Unbounded choices; min over options; `INF` for impossible | 1 |
| 416 | Partition Equal Subset Sum | 0/1 knapsack; iterate capacity *downward* in 1D | 1 |
| 139 | Word Break | Prefix state: "can `s[0..i)` be built?" | 1 |
| 91 | Decode Ways | Count ways with validity rules (Meta classic) | 1 |
| 300 | Longest Increasing Subsequence | "Best answer *ending at* i"; then the O(n log n) patience trick | 1 |
| 62 / 64 | Unique Paths / Minimum Path Sum | Grid: state = cell, choices = from top or left | 1 |
| 1143 | Longest Common Subsequence | Two strings → 2D state `(i, j)` | 1 |
| 72 | Edit Distance | Three choices per cell: insert, delete, replace | 1 |
| 647 | Palindromic Substrings | Interval state; or expand around centers | 2 |
| 329 | Longest Increasing Path in a Matrix | DFS + memo on an implicit DAG (graph meets DP) | 2 |
| 526 | Beautiful Arrangement | Bitmask memo: state = which numbers are used | 2 |
| 518 | Coin Change II | Count combinations, not permutations: loop order matters | 2 |
| 10 | Regular Expression Matching | Meta hard; `*` means zero or more of the previous char | 2 |
| 312 | Burst Balloons | Interval DP: pick the *last* balloon to burst | 2 |

```cpp
// Memoized recursion skeleton: fill in State, choices, base case.
unordered_map<long long, int> memo;                 // or a vector sized by the state space
int solve(State s) {
    if (isBase(s)) return baseValue(s);
    long long key = encode(s);
    if (auto it = memo.find(key); it != memo.end()) return it->second;
    int best = INIT;                                // INF for min, 0 for count/max
    for (auto c : choices(s))
        best = combine(best, cost(s, c) + solve(next(s, c)));
    return memo[key] = best;
}
```

**You have it when:** on five unseen DP problems in a row, you write the five answers above in under 5 minutes, before touching code.

## 4. Graph and state-space search ladder

Already scheduled ⓢ: 200, 133, 207, 210, 721, 743 (Dijkstra), 787 (Bellman-Ford), 269.

**Mental model: BFS over an FSM.** In a maze with keys, the node is not the cell. It is `(cell, keys held)`, exactly like a protocol FSM where the same input means something different in each session state. Visited must be tracked per full state.

**Hook: "What is a state?" before "Which algorithm?"**

| # | Problem | New idea at this rung | Tier |
| --- | --- | --- | --- |
| 994 | Rotting Oranges | Multi-source BFS: push every source at time 0 | 1 |
| 1091 | Shortest Path in Binary Matrix | Grid BFS, 8 directions; then redo with A* (§5) | 1 |
| 752 | Open the Lock | Implicit graph (neighbors are generated); dead ends; then bidirectional BFS | 1 |
| 127 | Word Ladder | Implicit graph over words; wildcard buckets for neighbors | 1 |
| 773 | Sliding Puzzle | State = whole board as a string; then redo with A* | 1 |
| 864 | Shortest Path to Get All Keys | **State = (r, c, keyMask).** Closest match to the reported maze stages | 1 |
| 1293 | Shortest Path in a Grid with Obstacles Elimination | State = (r, c, removals left) | 2 |
| 847 | Shortest Path Visiting All Nodes | Multi-source BFS over (node, visitedMask) | 2 |
| 490 / 505 | The Maze / The Maze II (Premium) | Rolling moves; BFS, then Dijkstra when step costs differ | 2 |
| 785 | Is Graph Bipartite? | Two-coloring with BFS | 2 |
| 547 / 684 | Number of Provinces / Redundant Connection | Union-find with path compression + union by rank | 2 |

```cpp
// BFS over (cell, keys); also records parents for path printing.
struct St { int r, c, keys; };
vector<vector<vector<int>>> dist(R, vector<vector<int>>(C, vector<int>(1 << K, -1)));
queue<St> q;
q.push({sr, sc, 0});
dist[sr][sc][0] = 0;
while (!q.empty()) {
    auto [r, c, keys] = q.front(); q.pop();
    if (done(keys)) return dist[r][c][keys];
    for (auto [dr, dc] : dirs) {
        int nr = r + dr, nc = c + dc;
        if (!inside(nr, nc) || wall(nr, nc) || lockedDoor(nr, nc, keys)) continue;
        int nk = keys | keyAt(nr, nc);              // picking up a key changes the state
        if (dist[nr][nc][nk] != -1) continue;
        dist[nr][nc][nk] = dist[r][c][keys] + 1;
        q.push({nr, nc, nk});
    }
}
```

**You have it when:** for any grid problem, you state the full state tuple and the size of the visited array (`R × C × 2^K`) before writing the loop.

## 5. A* search (1.5 h)

**Mental model: Dijkstra with a compass.** Dijkstra spreads like a ripple in a pond, in every direction. A* also prefers nodes that point toward the goal: priority = `g` (cost so far) + `h` (estimate to goal).

**The two rules to say in an interview:**
- **Admissible:** `h` never overestimates, so the first time you pop the goal, its cost is optimal.
- **Pick `h` to match the moves.** 4-direction grid: Manhattan distance. 8-direction grid (LC 1091): **Chebyshev** `max(|dr|, |dc|)`. Manhattan would overestimate a diagonal step and break optimality.

**Exercise:** solve 1091 and 773 with BFS, then with A*. Count nodes expanded by each. For 773, `h` = sum of each tile's Manhattan distance to its target position.

```cpp
// A*: Dijkstra with priority f = g + h. dist initialized to INF.
using T = tuple<int, int, int>;                     // f, g, node
priority_queue<T, vector<T>, greater<T>> pq;
dist[start] = 0;
pq.push({h(start), 0, start});
while (!pq.empty()) {
    auto [f, g, u] = pq.top(); pq.pop();
    if (u == goal) return g;
    if (g > dist[u]) continue;                      // stale entry
    for (auto [v, w] : neighbors(u)) {
        if (g + w < dist[v]) {
            dist[v] = g + w;
            pq.push({dist[v] + h(v), dist[v], v});
        }
    }
}
```

**Interview use:** in a maze scale-up stage, "BFS is optimal but explores in all directions; with a known goal, A* with Manhattan distance explores far fewer cells and is still optimal because the heuristic is admissible."

## 6. Minimax (1.5 h)

**Mental model: assume the other player is as good as you.** Score every move by the opponent's *best* reply, not their average one.

**Hook: score difference turns two players into one recursion.**
`best(state) = max over moves (what I gain − best(state after my move))`.
The opponent's best is subtracted, because whatever they get counts against you.

| # | Problem | New idea | Tier |
| --- | --- | --- | --- |
| 1275 | Find Winner on a Tic Tac Toe Game | Warm-up: win detection with row/col/diagonal counters | 2 |
| 486 | Predict the Winner | Score-difference recursion on `(i, j)`, then memoize | 1 |
| 877 | Stone Game | Same recursion; then the parity proof (first player always wins) | 2 |
| 464 | Can I Win | Minimax + bitmask memo: state = numbers already taken | 1 |
| 348 | Design Tic-Tac-Toe (Premium) | O(1) per move with counters; Meta-tagged design-a-class | 2 |

```cpp
// LC 486: best score difference the player to move can force on nums[i..j].
int best(int i, int j) {                            // add a memo on (i, j)
    if (i > j) return 0;
    return max(nums[i] - best(i + 1, j),
               nums[j] - best(i, j - 1));
}
// Player 1 wins (or ties) if best(0, n - 1) >= 0.
```

**Know by name:** alpha-beta pruning (stop exploring a move once it is already worse than an alternative), and depth limit + evaluation function for games too big to search fully.

**Fun fact for the card game:** picking three of 1–9 that sum to 15 is "Number Scrabble." The 8 winning triples are exactly the 8 lines of the 3×3 magic square, so the two-player version *is* tic-tac-toe.

## 7. MCTS: concept only (45 min)

Not reported, and not codeable well in 45 minutes. Know it well enough to name it as a scale-up idea.

**Mental model: adaptive routing with probes.** Send probes down paths, favor the ones with good measured results, but keep probing the others in case they are better. That balance is UCB1 (explore vs exploit), the same idea as a multi-armed bandit.

**Four steps:** select (follow UCB1 down the tree) → expand (add one child) → simulate (random playout to the end) → backpropagate (update win counts up the path).

**The part that was reported: Monte Carlo evaluation.** In the card game, a strategy is scored over many games. Practice: write a strategy function, simulate 10,000 random deals with a fixed seed, and report the success rate. Then improve the strategy (greedy → backtracking) and compare rates. That is a full AI-drill-sized exercise.

## How this fits Nov 5–20

Tier 1 is about 25 new problems (about 10–12 h at 25 min each plus review; 70/198 and 62/64 are quick pairs). Tier 2 is for after the loop or spare time. Two ways to fund it, pick one:

- **Swap:** replace 2–3 AI drills with the reported themes (below), and put the Tier 1 problems in the Fri Nov 13 and Wed Nov 18 "random mediums" slots.
- **Add:** a 45-minute slot each weekday Nov 5–18 (two problems a day). Keep the 90-minute minimum-day rule if that slips.

**AI drill swap suggestion:**

| Current drill | Swap for | Covers |
| --- | --- | --- |
| #2 KV store with TTL (Sun Nov 8) | Maze with walls, keys/doors, portals; print the path; then scale | State BFS, parent pointers, A* |
| #3 Log analyzer (Wed Nov 11) | Word-list solver: max unique characters; then 10× the word list | Backtracking, bitmasks, pruning |
| #5 Spreadsheet (Tue Nov 17) | Card game: pick 3 summing to 15; greedy, then backtracking; Monte Carlo score over 10k games | Search, DP, simulation |

Keep #1 (route table: your domain) and #4 (task scheduler: topological sort).

**Order:** backtracking first (Nov 5–9), DP next (Nov 10–14), state BFS + A* + minimax (Nov 15–18). DP builds on backtracking, so the order matters.

**Chosen (Nov 4): add a 45-min slot every weekday.** It is in each day's issue under "Ladder slot":

| Day | Theme | Problems |
| --- | --- | --- |
| Thu Nov 5 | Backtracking | 90, 39 |
| Fri Nov 6 | Backtracking | 22, 131 |
| Mon Nov 9 | Backtracking | 79, 51 |
| Tue Nov 10 | DP | Warm-up 70, 198, 62, 64 · 322 |
| Wed Nov 11 | DP | 416, 139 |
| Thu Nov 12 | DP | 91, 300 |
| Fri Nov 13 | DP | 1143, 72 |
| Sun Nov 15 | A* | 773 (BFS over board states, then A*) |
| Mon Nov 16 | State BFS | 994, 1091 (BFS, then A*) |
| Tue Nov 17 | State BFS | 752, 864, 127 |
| Wed Nov 18 | Minimax | 486, 464 |

With the loop on Fri Nov 20 (set Nov 4), 127 and 773 moved off the Nov 18 stretch line onto Nov 15 and Nov 17, so all of Tier 1 finishes before the taper day.

## Coaching format for each problem

1. Say the shape and the state before coding (the five DP questions, or the state tuple for BFS).
2. Brute force first, with its complexity.
3. Then the optimization, and name the trick (memo, bitmask, pruning rule, heuristic).
4. Log the miss with its pattern in `tracker/error-log.md`.
