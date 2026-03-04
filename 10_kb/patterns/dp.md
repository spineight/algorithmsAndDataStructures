# Dynamic programming (DP)

## Core idea
- Visualize recursion tree first.
- Define the subproblem (state) + transitions.
- Convert recursion -> memoization -> iterative DP.

## Backward DP trick
For state `dp[i]`, ask: “from which previous states can I arrive here?”
This helps define dependencies and iteration order.

## State storage optimization
Often you don’t need the whole DP table:
- If `dp[i]` uses only last K states, keep rolling variables / 2 rows.

## Answer reconstruction
If you need to restore solution:
- store `parent` pointers / choice decisions
- or infer decisions from the DP table (sometimes possible)