# Two pointers

This topic is broad. In interview prep, “two pointers” usually means one of these families:

1) **Sliding window** (most common): move `r` forward, move `l` to restore validity  
2) **Meet-in-the-middle** (often sorted): move `l` or `r` based on comparison  
3) **Fast/slow pointers**: linked list cycle, middle element, etc.

---

## TL;DR (2–5 min refresher)

### When to use
- You can maintain a window `[l..r]` with a small mutable **state** (counts / sum / distinct count / etc.).
- You can restore the required property by moving **only one pointer** (typically `l`) while the other (`r`) moves forward.
- Or the array is sorted and you can decide pointer moves from comparisons.

### Core invariant
For sliding window:
- After the inner “shrink” loop finishes, the window `[l..r]` is **valid** again.
- Each pointer moves monotonically forward ⇒ typically **O(n)**.

### Canonical templates (conceptual)

#### A) Sliding window (variable size)
- expand `r`
- update state with `a[r]`
- while invalid(state): remove `a[l]`, `l++`
- update answer

#### B) Meet-in-the-middle on sorted data
- start `l=0`, `r=n-1`
- if condition too small: `l++`
- if too large: `r--`
- record best / count / pairs

#### C) Fast/slow pointers
- slow moves 1 step
- fast moves 2 steps
- detect cycle / find middle / etc.

---

## Worked example #1 (Sliding window): LC 3 “Longest Substring Without Repeating Characters”

### Problem
Given a string `s`, find the length of the longest substring without repeating characters.

### State + invariant
- `freq[ch]` = how many times `ch` appears in current window `[l..r]`
- Invariant after shrinking: `freq[s[r]] <= 1` ⇒ no duplicates in window

### Implementation (C++17)
```cpp
#include <string>
#include <unordered_map>
#include <algorithm>

int lengthOfLongestSubstring(const std::string& s) {
  std::unordered_map<char, int> freq;
  int best = 0;
  int l = 0;

  for (int r = 0; r < (int)s.size(); ++r) {
    ++freq[s[r]];

    while (freq[s[r]] > 1) {
      --freq[s[l]];
      ++l;
    }

    best = std::max(best, r - l + 1);
  }
  return best;
}
````

### Quick trace (why shrinking works)

`s = "abba"`

* r=0 'a': window "a" valid
* r=1 'b': window "ab" valid
* r=2 'b': duplicate 'b' => move `l` until only one 'b' remains
* r=3 'a': valid again, update answer

### Typical pitfalls

* Off-by-one: length is `r - l + 1`
* Shrinking condition must match validity condition. If you shrink too little, invariant breaks; too much, you lose optimal answers.

---

## Worked example #2 (Meet-in-the-middle): “Container With Most Water” (LC 11)

### Key idea (why moving the shorter side is correct)

Area is `min(h[l], h[r]) * (r-l)`.
If `h[l] < h[r]`, moving `r--` cannot increase `min(h[l], h[r])` (still limited by `h[l]`),
but **will decrease width**, so it can’t help.
Therefore, when `h[l] < h[r]`, you move `l++` (try to find a taller left wall).

### Minimal C++ implementation

```cpp
#include <vector>
#include <algorithm>

int maxArea(const std::vector<int>& h) {
  int l = 0, r = (int)h.size() - 1;
  int best = 0;

  while (l < r) {
    best = std::max(best, std::min(h[l], h[r]) * (r - l));
    if (h[l] < h[r]) ++l;
    else --r;
  }
  return best;
}
```

---

## Common mistakes / debugging checklist

* **State updates must be symmetric**:

  * when `r` moves: add `a[r]`
  * when `l` moves: remove `a[l]`
* Always write (even briefly) the **validity condition** and the **invariant after shrinking**.
* If you get stuck, do what you wrote in `__MAIN__/README.md`: pen & paper + invariants + classifying edge cases.

---

## Practice progression (recommended order)

Goal: build intuition fast, then deepen.

### Level 0 — template drills (5–10 minutes total)

* Write sliding-window template from memory (no IDE).
* Write meet-in-the-middle template from memory.

### Level 1 — easy “mechanical” two pointers

* [LC 26] Remove Duplicates from Sorted Array (classic “slow/fast” write index)
* [LC 125] Valid Palindrome (two ends)
* [LC 88] Merge Sorted Array (end pointers)

### Level 2 — core interview problems (your Core Starter Set overlaps here)

* [LC 3] Longest Substring Without Repeating Characters (sliding window)
* [LC 11] Container With Most Water (meet-in-the-middle)
* [LC 15] 3Sum (sort + two pointers per fixed i)

### Level 3 — “deep two pointers” (do after Level 2 feels comfortable)

* [LC 42] Trapping Rain Water (two pointers with max-left/max-right invariant)
* [LC 76] Minimum Window Substring (hard sliding window)
* [LC 986] Interval List Intersections (pointer movement + careful boundaries)

Suggestion: don’t grind Level 1 too long. Do 1–2, then move to Level 2, and rely on revisits.

---

<details>
  <summary>Deep dive: variants, proofs, and implementation details</summary>

## Variant A: Sliding window with last-seen index (often faster than counts)

For LC 3 you can store last position of each char and jump `l`:

* `l = max(l, last[ch] + 1)`

This is often cleaner and avoids inner `while`, but you must be careful with `max(...)`.

## Variant B: Two pointers with “write index” (slow/fast)

Typical for “compress in-place”:

* `write` points to where to write next valid element
* `read` scans the array

Invariant:

* `a[0..write-1]` is the processed compacted prefix.

## Variant C: Trapping Rain Water invariant

Maintain:

* `maxLeft` for prefix, `maxRight` for suffix
  Move the side with smaller boundary because that side’s water is fully determined.

## Common correctness proof pattern

* State the invariant.
* Show it holds initially.
* Show each step preserves it.
* Argue termination and optimality:

  * sliding window: each element enters and leaves window at most once
  * meet-in-middle: moving the limiting side is the only chance to improve

</details>

<details>
  <summary>Sources (your repo)</summary>

* Main note hub with links and commentary:

  * `__MAIN__/README.md` (has "Two pointers" section and links to your implementations)
* Submodules referenced in your notes:

  * [https://github.com/spineight/leetcode](https://github.com/spineight/leetcode)
  * [https://github.com/spineight/pashka](https://github.com/spineight/pashka)

In local clone, your code paths mentioned in `__MAIN__/README.md` should work under the submodules.

</details>
```

When you’ve pasted this and you’re happy with it, reply **`finish`** and we’ll do **`10_kb/patterns/dp.md`** next (same style: TL;DR + worked example + deep dive + *your* existing links and “order of difficulty” from your notes).
