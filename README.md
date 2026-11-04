# Meta Interview Prep — Nov 1–19, 2026 · Loop Fri Nov 20

Tracking for a 3-week, ~100-hour prep plan for Meta's SWE loop. Each day is a GitHub issue with a checklist; close it when every box is ticked. Weekly progress lives in the milestones and the [scorecard](tracker/scorecard.md).

Full plan with playbooks and reading lists: [Meta Interview Prep — 3-Week Plan](https://claude.ai/artifact/Se2fSVfsmhqVznif4Uc7m8) (Claude doc, private to me).

## The loop

| Round | Length | Format |
| --- | --- | --- |
| Coding ×2 | 60 min each | One multi-part question in CoderPad, built-in AI assistant allowed (C++) |
| System design | 45 min | CoderPad + Mermaid diagrams, built-in AI assistant |
| In-domain design | 45 min | Networking / systems design, same tooling |
| Behavioral | 45 min | Scope and scale, technical expertise, XFN collaboration, AI-driven impact (STAR) |

## How to use this repo

1. **Each morning:** open today's issue (milestone for the current week, sorted oldest first). Start with a 15-min redo of yesterday's misses.
2. **During the day:** tick boxes as you finish. Commit solutions, designs and sheets into the folders below and link them in an issue comment.
3. **Anything that goes wrong:** add a row to the [error log](tracker/error-log.md). At work, add entries to the [AI-usage log](tracker/ai-usage-log.md).
4. **Every Saturday:** fill the [scorecard](tracker/scorecard.md) and run the [replan rules](tracker/replan-rules.md). Edit next week's issues to match and log the change.
5. **Missed items:** move them into tomorrow's issue, or take the 90-min minimum day (2 problems + 1 story or 1 design outline). Never cut mocks or sleep.

## Milestones

| Milestone | Dates | Theme | Exit check |
| --- | --- | --- | --- |
| Week 1 | Nov 1–7 | Foundations: baseline, core patterns, design framework, first stories | Scorecard targets for Nov 7 |
| Week 2 | Nov 8–14 | Depth and reps: graphs, design reps, AI drills, mocks #1–2 | Scorecard targets for Nov 14 |
| Week 3 | Nov 15–19 | Mocks, polish, taper: full self-loop, mock #4 (Mon Nov 16) and #3 (Wed Nov 18), no new material after Nov 18, taper Thu Nov 19 | Rested for the loop on Fri Nov 20 |

## Labels

`week-1` `week-2` `week-3` · `coding` `ai-drill` `system-design` `in-domain` `behavioral` `mock` · `refresh` (domain and open-source sheets) `systems` (systems programming sheets and exercises) · `review` (baseline, Saturday reviews, replan checkpoints)

## Layout

```
coding/
  leetcode/        one C++ file per problem: 1249_min_remove_parens.cpp
  ai-drills/       one folder per multi-part drill (see README)
design/
  system/          one .md per design with a Mermaid diagram
  in-domain/       one .md per in-domain prompt
behavioral/
  story-bank.md    10 STAR stories mapped to Meta's four signal areas
sheets/
  refresh/         one-page sheets: BGP, OSPF, EVPN-VXLAN, Kafka, ...
  systems/         one-page sheets + the two coding exercises
mocks/             debrief notes for the 4 external mocks + self-mock
tracker/           scorecard, replan rules, error log, AI-usage log
scripts/           create_issues.py + issues.json used to seed the issues
```
