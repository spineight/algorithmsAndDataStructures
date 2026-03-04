# Complexity basics (quick reload)

## Mental model
- RAM model: count primitive operations.
- Big-O: upper bound (worst), Ω: lower bound (best), Θ: tight bound.

## Typical signals
- One loop over `n` -> O(n)
- Nested loops -> often O(n^2)
- “Halving each time” -> O(log n)
- Sort -> O(n log n)

## Example anchor: insertion sort
- Best case (already sorted): Ω(n)
- Worst case (reverse sorted): O(n^2)

## Interview rule of thumb
If you can say:
- “time is O(...), space is O(...), and this invariant holds…”
you’re in a strong position.