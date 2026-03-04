# Practical optimizations

## Replace floating operations when you only need comparisons
When comparing values like averages, you can avoid division by multiplying by LCM.

## If you have 2 arrays, process the smaller one
Useful for intersection and frequency-based solutions.

## Space optimization: reuse input storage (when safe)
Example idea: mark presence by flipping sign / adding offsets, when values allow it.

## Sorting indices instead of heavy objects
If `elements` are heavy or comparisons are expensive, sort indices and refer back to data.