#!/usr/bin/env python3
"""Seed labels, milestones and daily issues from issues.json.

Usage:  python3 scripts/create_issues.py [owner/repo]
Needs the GitHub CLI (`gh auth login`). Safe to re-run: existing labels,
milestones and issues (matched by title) are skipped.
"""
import json
import os
import subprocess
import sys

REPO = sys.argv[1] if len(sys.argv) > 1 else "pravinadin/meta-interview-prep"
HERE = os.path.dirname(os.path.abspath(__file__))

LABELS = {
    "week-1": ("0E8A16", "Week 1 (Nov 1–7): Foundations"),
    "week-2": ("FBCA04", "Week 2 (Nov 8–14): Depth and reps"),
    "week-3": ("D93F0B", "Week 3 (Nov 15–20): Mocks, polish, taper"),
    "coding": ("1D76DB", "LeetCode problems and timed coding"),
    "ai-drill": ("5319E7", "Multi-part AI-enabled coding drill"),
    "system-design": ("0052CC", "System design practice"),
    "in-domain": ("006B75", "Networking / systems in-domain design"),
    "behavioral": ("C5DEF5", "STAR stories and rehearsal"),
    "mock": ("B60205", "External or self-run mock interview"),
    "refresh": ("BFD4F2", "Domain and open-source refresh sheets"),
    "systems": ("D4C5F9", "Systems programming sheets and exercises"),
    "review": ("FEF2C0", "Baseline, Saturday review, replan checkpoint"),
}

# Due at the end of the last day of each week, Pacific time (PST = UTC-8).
MILESTONES = {
    "Week 1": ("2026-11-08T07:59:59Z", "Nov 1–7 · Foundations: baseline, core patterns, design framework, first stories"),
    "Week 2": ("2026-11-15T07:59:59Z", "Nov 8–14 · Depth and reps: graphs, design reps, AI drills, mocks #1–2"),
    "Week 3": ("2026-11-21T07:59:59Z", "Nov 15–20 · Mocks, polish, taper; no new material after Nov 18"),
}


def gh(*args, data=None):
    cmd = ["gh", "api", *args]
    if data is not None:
        cmd += ["--input", "-"]
    out = subprocess.run(cmd, input=json.dumps(data) if data is not None else None,
                         capture_output=True, text=True)
    if out.returncode != 0:
        raise SystemExit(f"gh api {' '.join(args)} failed:\n{out.stdout}{out.stderr}")
    return json.loads(out.stdout) if out.stdout.strip() else None


def main():
    issues = json.load(open(os.path.join(HERE, "issues.json")))

    have = {l["name"] for l in gh(f"repos/{REPO}/labels?per_page=100")}
    for name, (color, desc) in LABELS.items():
        if name not in have:
            gh(f"repos/{REPO}/labels", data={"name": name, "color": color, "description": desc})
            print("label     +", name)

    ms = {m["title"]: m["number"] for m in gh(f"repos/{REPO}/milestones?state=all&per_page=100")}
    for title, (due, desc) in MILESTONES.items():
        if title not in ms:
            ms[title] = gh(f"repos/{REPO}/milestones",
                           data={"title": title, "due_on": due, "description": desc})["number"]
            print("milestone +", title)

    existing = {i["title"] for i in gh(f"repos/{REPO}/issues?state=all&per_page=100")
                if "pull_request" not in i}
    for it in issues:  # issues.json is in date order, so issue numbers follow the calendar
        if it["title"] in existing:
            continue
        n = gh(f"repos/{REPO}/issues", data={
            "title": it["title"], "body": it["body"],
            "labels": it["labels"], "milestone": ms[it["milestone"]],
        })["number"]
        print(f"issue     #{n}", it["title"])


if __name__ == "__main__":
    main()
