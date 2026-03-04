# Common mistakes (interview + contests)

## Use pen & paper / invariants
- Write loop invariants and function-call invariants.
- Draw call stack / call frames when recursion gets confusing.

## Corner cases
### Integer overflow
- Beware of comparisons like `a < b + c` (the sum can overflow).
- Beware of `i*i` when scanning factors; `i*i` can overflow for `int`.

### Short-circuit evaluation can skip work
If you write something like:
- `isOk = isOk && DFS(...)`
and `isOk` becomes `false`, DFS will stop being called (because of short-circuit).

Fix patterns:
- Evaluate first, then combine:
  - `bool child = DFS(...); isOk = isOk && child;`
- Or use bitwise `&` on bool (no short-circuit):
  - `isOk = isOk & DFS(...);`  (works, but be explicit in comments)

### “Looks correct” but forgot the final check
Classic example: stack problems (brackets).
Even if all characters processed, you must still verify `stack.empty()`.

## TODO (fill as you meet them)
