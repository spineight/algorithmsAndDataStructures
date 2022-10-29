//! https://app.codility.com/programmers/lessons/7-stacks_and_queues/brackets/

/*


A string S consisting of N characters is considered to be properly nested if any of the following conditions is true:

        S is empty;
        S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
        S has the form "VW" where V and W are properly nested strings.

For example, the string "{[()()]}" is properly nested but "([)()]" is not.

Write a function:

    int solution(string &S);

that, given a string S consisting of N characters, returns 1 if S is properly nested and 0 otherwise.

For example, given S = "{[()()]}", the function should return 1 and given S = "([)()]", the function should return 0, as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [0..200,000];
        string S is made only of the following characters: "(", "{", "[", "]", "}" and/or ")".
 */

#include <stack>
#include <unordered_map>
int solution(string &S) {
  stack<char> s;
  unordered_map<char, char> closedMatch {
          {'(', ')'},
          {'{', '}'},
          {'[', ']'} };
  for(auto ch : S) {
    if(ch == '(' || ch == '{' || ch == '[')
      s.push(ch);
    else {
      if(s.empty() || closedMatch[s.top()] != ch)
        return 0;
      s.pop();
    }
  }
  return s.empty(); //! NB!!!
}