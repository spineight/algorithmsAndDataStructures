### Segment Tree
### Basic implementation ideas
see segmentTreeSum.cpp

#### associative operation
any associative operation `@` could be used  
an operation `@` is associative if:  
`(x @ y) @ z = x @ (y @ z)`
examples of associative operations:
+, min, gcd, xor, bitwise |,&
minCount - number of element on the segment equal to min on the segment

#### node
there are internal nodes and leafs  
an internal node stores the result of operation applied to the segment (lx,rx) it is responsible for
