#### Lecture 8 : Hashing with chaining
Abstract Data Type (ADT) - Dictionary operations with it  

mapping of object from a very large set (size n) to a smaller set (size m)  
*prehashing* - mapping an object to some positive number (might be > m)  
*hashing* - positive number is mapped in 0..m  
if n > m then by pigeon hole principle several objects might end in one number - collision  
`n/m = \alpha` - load factor  

Ways to resolve collisions - chaining (discussed in this lecture), open addressing (discussed in further lecture)  

Gave examples of hash function calculations  

##### Lecture 9 : Table doubling, Rabin-Karp
###### Table doubling 
on the resizing policy when number of inserted items (n) became >= number of keys (m)  
If we double m every time n >= m we will get O(1) ammortized insert  
For delete we half the size every time size = m / 4 (when full only on 1/3)  

There are techniques that allows to do on O(1) non armotized,
at certain moment you preallocate a new table of size 2m and every time you insert a new element - you copy k elements
to a new table, and after certain moment you switch tables  

###### Rabin-Karp  
text - size n, pattern - size m
Ideas: sliding window of size m,
use hash to compare 2 strings of size m,
hash for a string - string can be viewd as a number base Z (where Z is a size of alphabet)  
every letter within the string can be viewed as a digit base Z  
to do hash computations efficient use rolling hash  

rolling hash idea - sliding window of size m, you move it one to the right on each step,
s - window offset in the text  
`rs -> rs+1` --> when you do this transition (a slide) you strip off the leftmost character (digit) and add on digit to the right  
`rs+1 = rs - s[i] * h + s[i+m] % m`  
where `h = d^(m-1)` is precomputed in order not to compute it each time  
`m` - is used to make sure res fits within a machine word (adviced to have some large random prime for it)  

spurious hit - it is possible that different strings maps to the same hash,  
hence it is required to do check for every potential match
