# Two pointers

## When to use
- You maintain a window `[l..r]` (substring/subarray).
- You need “shrink from left while condition broken”.

## Core invariant
- The window represents a valid state; when invalid, advance `l` until valid again.

## Template (conceptual)
- Expand `r`
- Update counts/state
- While invalid: shrink `l`
- Update best answer

## Anchor problems (link your solutions here)
- Longest substring without repeating characters
- Trapping rain water