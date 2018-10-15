/*
Description

Farmer John has constructed an obstacle course for the cows' enjoyment. The course
consists of a sequence of N fences (1 <= N <= 50,000) of varying lengths, each
parallel to the x axis. Fence i's y coordinate is i.

The door to FJ's barn is at the origin (marked '*' below). The starting point of
the course lies at coordinate (S,N).

   +-S-+-+-+        (fence #N)

 +-+-+-+            (fence #N-1)

     ...               ...

   +-+-+-+          (fence #2)

     +-+-+-+        (fence #1)

=|=|=|=*=|=|=|      (barn)

-3-2-1 0 1 2 3

FJ's original intention was for the cows to jump over the fences, but cows are much
more comfortable keeping all four hooves on the ground. Thus, they will walk along
the fence and, when the fence ends, they will turn towards the x axis and continue
walking in a straight line until they hit another fence segment or the side of the
barn. Then they decide to go left or right until they reach the end of the fence
segment, and so on, until they finally reach the side of the barn and then, potentially
after a short walk, the ending point.

Naturally, the cows want to walk as little as possible. Find the minimum distance
the cows have to travel back and forth to get from the starting point to the door
of the barn.
Input

* Line 1: Two space-separated integers: N and S (-100,000 <= S <= 100,000)

* Lines 2..N+1: Each line contains two space-separated integers: A_i and B_i
(-100,000 <= A_i < B_i <= 100,000), the starting and ending x-coordinates of fence
segment i. Line 2 describes fence #1; line 3 describes fence #2; and so on. The
starting position will satisfy A_N <= S <= B_N. Note that the fences will be traversed
in reverse order of the input sequence.
Output

* Line 1: The minimum distance back and forth in the x direction required to get
from the starting point to the ending point by walking around the fences. The
distance in the y direction is not counted, since it is always precisely N.

Sample Input

4 0
-2 1
-1 2
-3 0
-2 1
Sample Output

4
Hint

This problem has huge input data,use scanf() instead of cin to read data to avoid
time limit exceed.

INPUT DETAILS:

Four segments like this:

   +-+-S-+             Fence 4

 +-+-+-+               Fence 3

     +-+-+-+           Fence 2

   +-+-+-+             Fence 1

 |=|=|=*=|=|=|         Barn

-3-2-1 0 1 2 3

OUTPUT DETAILS:

Walk positive one unit (to 1,4), then head toward the barn, trivially going around
fence 3. Walk positive one more unit (to 2,2), then walk to the side of the barn.
Walk two more units toward the origin for a total of 4 units of back-and-forth walking.
*/

#include <iostream>
#include <cstdio>
#include <cmath>

#define INF 0x7fffffff

using namespace std;

int N, S;

int fence[50005][2];
long dp[50005][2]; // dp[i][j]: minDist to left side(0) or right side(1) of #i fence
long minDist = INF;

int main() {
  scanf("%d %d", &N, &S);
  for (int i=1; i<=N; i++) {
    scanf("%d %d", &fence[i][0], &fence[i][1]);
  }

  dp[N][0] = S - fence[N][0];
  dp[N][1] = fence[N][1] - S;

  for (int i=N-1; i>=1; i--) {
    dp[i][0] = INF;
    dp[i][1] = INF;
    int ll = fence[i][0], rl = fence[i][1];
    for (int j=i+1; j<=N; j++){
      if (fence[j][0]<rl && fence[j][0]>ll && fence[j][1]>rl) {
        rl = fence[j][0];
        dp[i][0] = min(dp[i][0], dp[j][0]+fence[j][0]-fence[i][0]);
        dp[i][1] = min(dp[i][1], dp[j][0]+fence[i][1]-fence[j][0]);
      }
      if (fence[j][1]<rl && fence[j][1]>ll && fence[j][0]<ll) {
        ll = fence[j][1];
        dp[i][0] = min(dp[i][0], dp[j][1]+fence[j][1]-fence[i][0]);
        dp[i][1] = min(dp[i][1], dp[j][1]+fence[i][1]-fence[j][1]);
      }
      if (fence[j][0]>ll && fence[j][1]<rl) {
        ll = fence[j][0];
        rl = fence[j][1];
        dp[i][0] = min(dp[i][0], dp[j][0]+fence[j][0]-fence[i][0]);
        dp[i][0] = min(dp[i][0], dp[j][1]+fence[j][1]-fence[i][0]);
        dp[i][1] = min(dp[i][1], dp[j][0]+fence[i][1]-fence[j][0]);
        dp[i][1] = min(dp[i][1], dp[j][1]+fence[i][1]-fence[j][1]);
      }
      if ((fence[j][0]<ll && fence[j][1]>rl) || ll>rl) {
        break;
      }
    }
  }

  for (int i=N; i>=1; i--) {
    int flag = 0;
    for (int j=i-1; j>=1; j--) {
      if (fence[i][0]>fence[j][0]) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      minDist = min(minDist, dp[i][0]+abs(fence[i][0]));
    }
    flag = 0;
    for (int j=i-1; j>=1; j--) {
      if (fence[i][1]<fence[j][1]) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      minDist = min(minDist, dp[i][1]+abs(fence[i][1]));
    }
  }

  printf("%ld\n", minDist);

  return 0;
}
