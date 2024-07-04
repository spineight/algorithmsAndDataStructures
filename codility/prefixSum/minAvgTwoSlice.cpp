//! https://app.codility.com/programmers/lessons/5-prefix_sums/min_avg_two_slice/

//! 10/15/2022
/*


A non-empty array A consisting of N integers is given. A pair of integers (P, Q), such that 0 ≤ P < Q < N, is called a slice of array A (notice that the slice contains at least two elements). The average of a slice (P, Q) is the sum of A[P] + A[P + 1] + ... + A[Q] divided by the length of the slice. To be precise, the average equals (A[P] + A[P + 1] + ... + A[Q]) / (Q − P + 1).

For example, array A such that:
    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8

contains the following example slices:

        slice (1, 2), whose average is (2 + 2) / 2 = 2;
        slice (3, 4), whose average is (5 + 1) / 2 = 3;
        slice (1, 4), whose average is (2 + 2 + 5 + 1) / 4 = 2.5.

The goal is to find the starting position of a slice whose average is minimal.

Write a function:

    int solution(vector<int> &A);

that, given a non-empty array A consisting of N integers, returns the starting position of the slice with the minimal average. If there is more than one slice with a minimal average, you should return the smallest starting position of such a slice.

For example, given array A such that:
    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8

the function should return 1, as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [2..100,000];
        each element of array A is an integer within the range [−10,000..10,000].


 */

//! 10/15/2022
//! Solved based on this: https://codesays.com/2014/solution-to-min-avg-two-slice-by-codility/
//! The key to solve this task is these two patterns:
//!     (1) There must be some slices, with length of two or three, having the minimal average value among all the slices.
//!     (2) And all the longer slices with minimal average are built up with these 2-element and/or 3-element small slices.
//!
//! Firstly we will prove the statement (1).
//! In all the following discussion, we assume the slices have two or more element.
//! In every array, there must be at lease one slice, to say S, having the Minimal Average (MA).
//! And PLEASE PAY ATTENTION, the following proof is done with the S, which HAS the global minimal average.
//!     a. If the length of S is two or three, it follows our conclusion.
//!     b. If the length of S is odd, we could divide it into a 3-element sub-slice and some 2-element sub-slice.
//!         For example, for the slice [1, 2, 3, 4, 5], we could get a 3-element sub-slice [1, 2, 3] and a 2-element sub-slice [4, 5].
//!         Or differently we could get [1, 2] and [3, 4, 5]. But the split does not matter in the following prove.
//!         -   If the sub-slices have different averages, some of them will have smaller average than MA.
//!             But it conflicts with the condition that, the MA is known as the global minimal average for all slices.
//!             By this contradictory, it’s proved that all the sub-slices MUST have the same average.
//!         -   If all the sub-slices have the same average, the average of them must be MA.
//!             So all these sub-slices have overall minimal average and length of two or three.
//!     c. If the length of S is even, we could divide it into some 2-element sub-slice.
//!         For the slice [1, 2, 3, 4], the only possible split is [1, 2] and [3, 4].
//!         Then, similar with the previous case, all these 2-element sub-slices have the global minimal average.
//! And in the construction in step b, we have already proven the statement (2).
//!
//! UPDATE 03-13-2014: We are NOT proving that, 4-or-more-element slices cannot have the global minimal average.
//! We just proved that, there MUST be some 2-element and/or 3-element slices, having the global minimal average.
//! In other words, we are NOT SURE whether there are some 4-or-more-element slices holding global minimal average.
//! But we are ONE HUNDRED PERCENT SURE about the 2-element and/or 3-element slices.
//
//! UPDATE 03-02-2015: There is another excellent discussion in the comments by Kim. Thanks!
//
//! UPDATE 03-14-2016: If you had any question about the statement
// “If the sub-slices have different averages, some of them will have smaller average than MA”,
// please read this comment and this comment. Thanks!

//! Good explanation
/*
  Despite all the effort, I failed to solve this problem.
  Only after I saw the article, I could finally realize that this was not a coding problem, but a mathematical one.
  I was deeply sad about this, but did not want to stop the challenge.
  So below is my own interpretation of the problem (or excuse for the failure I have made.)

  So basically the problem is to prove next statement.
  Let len(s) be the length of a slice s, sum(s) the sum of the all elements of the slice s,
  and ave(s) the average of the slice s.
  Then for an arbitrary array, every slice s having len(s) > 3 contains a sub-slice s’ such that ave(s) >= ave(s’).

 Proof.
  Suppose that s is a slice having len(s) > 3 and does NOT contain a sub-slice s’ such that ave(s) >= ave(s’).
  Since len(s) > 3, s can be divided into sub-slices t and u.
 Then,
  ave(t) = sum(t) / len(t), and ave(u) = sum(u) / len(u).
  ave(s) = sum(s) / len(s)
  = [sum(t) + sum(u)] / [len(t) + len(u)]
  = [len(t) * ave(t) + len(u) * ave(u)] / [len(t) + len(u)].
  If ave(u) >= ave(t) then let s’ be t
  ave(s) = [len(t) * ave(t) + len(u) * ave(u)] / [len(t) + len(u)]
  >= [[len(t) + len(u)] * ave(t)] / [len(t) + len(u)]
  = ave(t)
  = ave(s’).
  Otherwise, if ave(t) >= ave(u) then let s’ be u
  ave(s) = [len(t) * ave(t) + len(u) * ave(u)] / [len(t) + len(u)]
  >= [[len(t) + len(u)] * ave(u)] / [len(t) + len(u)]
  = ave(u)
  = ave(s’).
This leads a contradiction, and completes the proof.
ps. After writing this note, I saw a counter example [8, 0, 0, 8] as Hunter2 indicated.
 A workaround of this is to permit a slice having length of one,
 although the problem description defines a slice to contain at least two elements.
 I guess that doing this does not harm the soundness of the proof.
 The point is to ignore all slices having the length of 4 or more, not to consider the slice having length of one.
 For example, you may argue that [0, 8, 1, 1] can be splitted into [0] and [8, 1, 1],
 but we can simply ignore [0] and take [1, 1] instead.
 */

/*
 Updated:
Uncomfortable with the postscript I wrote,
 I thought a little more on the proof, and figured out that the postscript above was absolutely NOT necessary.
 As a matter of fact, at first time I was confused with [8, 0, 0, 8] as Hunter2 indicated
 and introduced a slice having length of one. But the real point was in a different place.
In the example slice [8, 0, 0, 8] what we want to claim IS that the average of [8, 0, 0, 8], which is 4,
 is greater than or equals the average of [8, 0] or [0, 8], which is also 4.
 Hence [8, 0, 0, 8] can be divided into sub-slices having the same or lower average value.
 It is important that we do NOT claim that the minimal average slice is [8, 0] or [0, 8].
 Finding the minimal average slice is another job to do later and that job is to examine slices of size 2 or 3.
Finally thanks to Sheng for the insight. I could never imagine the idea behind the solution without his comment.
 */

/*
  One more thing.
When I saw the claim that examining 2-3 slices is enough, what struck immediately in my mind was the mathematical induction.
 Probably most of us have the experience of proving next statement, that is;
every integer greater than 3 can be expressed as a linear combination of 2 and/or 3.
Then I realized that the same principal can be applied to this problem.
 How stupid I am! Rest of the problem was not so hard.
 In fact, I did not even try to code, because sometimes if once a solution is found, it is not much meaningful to code it.
However I feel that I’m fortunate since I still have the textbook of discrete mathematics. I should revisit it once more.
Lastly, I guess that I talked too much alone at this time. Sorry for your inconvenience. Enjoy happy coding!
 */


//! Based on this solution
#include <limits>
int solution(vector<int> &A) {
  const size_t n{A.size()};
  int best{numeric_limits<int>::max()};
  int bestPos{0};
  for(size_t i = 0; i < n-2; ++i) {
    // twoSlice / 2
    // threeSlice / 3
    // *6 ->
    // twoSlice * 3
    // threeSlice * 2
    const int twoElemSlice = (A[i] + A[i+1]) * 3;
    const int threeElemSlice = (A[i] + A[i+1] + A[i+2]) * 2;
    const int curMin = min(twoElemSlice, threeElemSlice);
    if(best > curMin) {
      best = curMin;
      bestPos = i;
    }
  }
  // check for last twoSlice
  const int twoElemSlice = (A[n-1] + A[n-2]) * 3;
  if(best > twoElemSlice)
    bestPos = n-2;
  return bestPos;
}

//! 13/11/2023
//! Looked up the previous solution
int solution(vector<int> &A) {
  const int n = A.size();
  //vector<int> prefixSum(n+1,0);
  //   for(int i = 1; i <=n; ++i) {
  //     prefixSum[i] = prefixSum[i-1] + A[i-1];
  //}
  int idx{0};
  double best{ (A[0] + A[1]) / 2.};

  for(int i = 0; i < n; ++i) {
    if(i + 1 < n) {
      double soFar = (A[i] + A[i+1]) / 2.;
      if(best > soFar) {
        best = soFar;
        idx = i;
      }
    }
    if(i + 2 < n) {
      double soFar = (A[i] + A[i+1] + A[i+2]) / 3.;
      if(best > soFar) {
        best = soFar;
        idx = i;
      }
    }
  }
  return idx;
}

//! 28/05/2024
int solution(vector<int> &A) {
    // Idea: the slice of min avg can be of length 2 or 3
    // (a+b) /2 > (a+b+c)/3
    // (a+b) / 2 > c
    // ex. 5 4 4
    double best = (A[0] + A[1]) / 2.;
    size_t pos{0};
    const size_t n = A.size();
    for(size_t i = 0; i + 1 < n; ++i) {
        const double avg2 = (A[i] + A[i+1]) / 2.;
        const double avgRes = (i + 2 < n) ? min( (A[i] + A[i+1] + A[i+2]) / 3., avg2) : avg2;
        if( best > avgRes ) {
            pos = i;
            best = avgRes;
        }
    }
    return pos;
}