#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol1246;

/*
Example 1:
Input: arr = [1,2]
Output: 2
*/
tuple<vector<int>, int>
testFixture1()
{
  return make_tuple(vector<int>{1, 2}, 2);
}

/*
Example 2:
Input: arr = [1,3,4,1,5]
Output: 3
Explanation: Remove [4] then remove [1,3,1] then remove [5].
*/
tuple<vector<int>, int>
testFixture2()
{
  return make_tuple(vector<int>{1, 3, 4, 1, 5}, 3);
}

void test1()
{
  auto f = testFixture1();
  cout << "Test 1 - exepct to see " << to_string(get<1>(f)) << endl;
  auto result = Solution::minMoves(get<0>(f));
  cout << "result: " << to_string(result) << endl;
}
void test2()
{
  auto f = testFixture2();
  cout << "Test 2 - exepct to see " << to_string(get<1>(f)) << endl;
  auto result = Solution::minMoves(get<0>(f));
  cout << "result: " << to_string(result) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}