cs106b Programming abstractions, Stanford
2008
Julie Zelenski 

### intro
get help solving the problem from coworkers(clones) who work and act like you do:
- delegate similar,smaller problem to clone
- combine result from clone(s)  to solve total problem

### Functional recursion
Function that returns answer/result:
- result for big problem uses result from smaller, same problem(s)

2 cases:

Base case:
- simplest version of problem
- can be directly solved

Recursive case:
- Makes one or more calls to self to get results for smaller, simpler version
- Recursive calls must advance toward base case
- Results of recursive calls combined(assembled) to solve larger version


### ideas
Feels mysterious at first:
"Leap of faith" required 

### thinking recursively

#### recursive decomposition
finding a self-similarity in problem

#### common patterns
- handle first and/or last, recur on remaining
- Divide in half, recur on one/both halves
- make a choice among options, recur on updated state (leaves you in a state where fewer choices to be made,
to try you a few decisions from there to work towards some base case)

#### Placement of recursive call(s)
recur-then-process versus process-then-recur

### Procedural VS Functional
Functional:
-returns result
- computes using result from recursive call(s)
Procedural:
- no return value
- task accomplished during recursive calls
Example: drawing fractal

### problems types
many problems in the end just boil down to an instance of either permutation problem or subset problem
permutation/ subsets are about choice
both have deep/wide tree of recursive calls
Depth represents total number of decisions made
Width of branching (how many recursive calls were made at each level of recursion) represents number of available options per decision

exhaustive recursion 
explores every possible option at every decision point 

we can take the same structure of the problem although it fundamentally could be exhaustive,
and only explore some part of the tree
If we get to some decisions that are good enough we don't need keep working any further


I am gonna show you how we take an exhaustive recursion problem and turn it into what is called recursive back tracking

Recursive backtracking
Cast problem in terms of decision points
- identify what decisions need to be made
- Identify what options are available for each decision
- A recursive call makes one decision, and recurs on remaining decisions

Backtracking approach
- Design recursion function to return success/failure
- at each call, choose one option and go with it
- Recursively proceed and see what happens
- If it works out, great, otherwise unmake choice and try again
- If no option worked, return fail result which triggers backtracking (i.e. un-making erlier decisions)

Heuristics may help efficiency
- eliminate dead ends early by pruning
- pursue most likely choice(s) first 

Backtracking pseudocode
```c++
bool Solve(configuration conf) {
  if(no more choices) // BASE CASE
    return (conf is goal state);

  for(all avaiable choices) {
    try one choice c;
    // solve from here, if works out, you're done
    if(Solve(conf with choice c made)) return true;
    unmake choice c;
  }
  return false; // tried all choices, no soln found, we conclude that configuration given this call was unsolvable
}
```

backtracking is comming back to an earlier decision you have made and unmaking it

Advice: try to make the backtracking function as simple as possible by putting in some helper functions,
that makes the code much easier to read (see 8 Queens problem)

Using simple heuristics - information you have about the domain can help you to guide your choice,
this also could help pruning down those things that are not worth looking at,
it doesn't change what the recursion does - the same backtracking and the recursion strategy is the same in all these problems,
what you trying to do is to pick your options looking at the choices you have and try to decide what are the most likely onces
and which once are not worth trying, so directing your decision making from the stand point of trying to make sure that you don't violate constraints


### Looking for patterns
The patterns we are seeing are more alike than are different:
solving sudoku, solving 8 queens, find an anagram in a sequence of letters, they all have this general idea of
being these decisions you are making.
Two problems I call them master or mother problem: permutations & subset problem are kind of fundamental to adapting them to these other domains

 