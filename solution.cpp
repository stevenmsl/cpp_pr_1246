#include "solution.h"
#include "util.h"
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
#include <math.h>

using namespace sol1246;
using namespace std;

/*takeaways
  - each number in the array is a palindrome so we can remove them
    one by one, which is the worst case
  - we will start by looking at all sub-arrays of a given length
    and calculate the moves required to remove them in a series
    of palindromes. When calculating the moves required for
    a longer array, it's based on the work done on the shorter
    arrays - bottom-up approach
  - let's use [1,3,4,1,5] as an example
    - sub-arrays of length 3
      - [1,3,5] so dp[0][2] = 3, 3 steps required to remove everything
      - [3,4,1] dp[1][3] = 3, and [4,1,5] dp[2,4] = 3
    - sub-arrays of length 4
      - [1,3,4,1]
        - you remove 1 in nums[0], then remove [3,4,1]
          - the total moves are dp[0][3] = 1 + dp[1][3] = 4
        - or you can remove nums[0], and nums[1] ALONG
          with [3,4], dp[1][2]
          - the total moves are dp[1][2],
            so dp[1][3] = dp[1][2] = 2
        - so find the minmun of these two options, so dp[0][3] = 2

    - sub-arrays of length 5 [1,3,4,1,5]
      - option 1, remove 1 in nums[0] then remove[3,4,1,5]
        - dp[0][4] = 1 + dp[1][4] = 1 + 4 = 5
      - option 2, remove 1 in nums[0] and nums[3] along with
        nums[2..3], which is the sub-array [3,4] and then nums[4]
        , which is [5]
        - dp[0][4] = dp[1][2] + dp[4][4] = 2 + 1 = 3
        - what does it mean to remove 1 in nums[0] and nums[3] along with
          nums[2..3]?
          - [1,3,4,1] -> remove 3 -> [1,4,1] -> remove all -> []
            - 2 steps
          - [1,3,4,1] -> remove 4 -> [1,3,1] -> remove all -> []
            - 2 steps
*/

int Solution::minMoves(vector<int> &nums)
{

  const int n = nums.size();

  /*record min steps required to remove nums[i..j]
    in a series of palindromes
  */
  auto dp = vector<vector<int>>(n, vector<int>(n, 0));

  /* look at all possible combinations from every different array size*/
  for (int len = 1; len <= n; ++len)
    /* j is pointing to the end of the array of length "len" */
    for (int i = 0, j = len - 1; j < n; ++i, ++j)
    {
      /*this is the baseline - you need one move to remove one number */
      if (len == 1)
      {
        dp[i][j] = 1;
        continue;
      }

      /* start with the worst case
         - we need to remove nums[i] as a solo
           palindrome itself
         - so 1 + remove nums[i+1..j] in a
           series of palindromes
      */
      dp[i][j] = 1 + dp[i + 1][j];

      /* check adjacent
         - how about remove nums[i..i+1] as a
           palindrome and then remove nums[i+2..j]
           in a series of palindromes?
           - 1 + dp[i + 2][j]
      */
      if (nums[i] == nums[i + 1])
        dp[i][j] = min(dp[i][j], 1 + dp[i + 2][j]);

      /* check tail
         - check if removing nums[i] nums[j] along with
           nums[i+1..j-1] in a series of palindromes
         - note that it will NOT take an additional
           step as nums[i] and nums[j] can be removed
           along with nums[i+1..j-1]
         - we DON't do this 1 + dp[i + 1][j - 1]
      */
      if (nums[i] == nums[j] && j > i + 1)
        dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);

      /*check in-between */
      for (int k = i + 2; k < j; ++k)
        /*tricky part!
          - see if we can remove nums[i] and nums[k]
            along with nums[i+1..k-1] and yield
            fewer moves
          - note the total moves are still dp[i+1][k-1]
            as we do NOT need an extra move to remove
            nums[i] and nums[k]!
        */
        if (nums[i] == nums[k])
          dp[i][j] = min(dp[i][j], dp[i + 1][k - 1] + dp[k + 1][j]);
    }

  return dp[0][n - 1];
}