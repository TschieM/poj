/*
Description

Gigel has a strange "balance" and he wants to poise it. Actually, the device is
different from any other ordinary balance.
It orders two arms of negligible weight and each arm's length is 15. Some hooks
are attached to these arms and Gigel wants to hang up some weights from his collection
of G weights (1 <= G <= 20) knowing that these weights have distinct values in the
range 1..25. Gigel may droop any weight of any hook but he is forced to use all
the weights.
Finally, Gigel managed to balance the device using the experience he gained at the
National Olympiad in Informatics. Now he would like to know in how many ways the
device can be balanced.

Knowing the repartition of the hooks and the set of the weights write a program
that calculates the number of possibilities to balance the device.
It is guaranteed that will exist at least one solution for each test case at the
evaluation.

Input

The input has the following structure:
•	the first line contains the number C (2 <= C <= 20) and the number G (2 <= G <= 20);
•	the next line contains C integer numbers (these numbers are also distinct and sorted
in ascending order) in the range -15..15 representing the repartition of the hooks;
each number represents the position relative to the center of the balance on the X
axis (when no weights are attached the device is balanced and lined up to the X axis;
the absolute value of the distances represents the distance between the hook and
the balance center and the sign of the numbers determines the arm of the balance
to which the hook is attached: '-' for the left arm and '+' for the right arm);
•	on the next line there are G natural, distinct and sorted in ascending order
numbers in the range 1..25 representing the weights' values.

Output

The output contains the number M representing the number of possibilities to poise
the balance.

Sample Input
2 4
-2 3
3 4 5 8

Sample Output
2
*/

#include <iostream>

using namespace std;

#define FIX 8000
#define MAXC 21
#define MAXG 21
#define MAXT 16000

int C, G;
int d[MAXC], w[MAXG];
int dp[MAXG][MAXT]; // 前 i 个质量块， 用 j 个， 产生的力矩为 k 时， 有多少种组合

int main() {
  cin >> C >> G;
  for (int i=1; i<=C; i++) {
    cin >> d[i];
  }
  for (int i=1; i<=G; i++) {
    cin >> w[i];
  }

  for (int i=0; i<MAXG; i++) {
    for (int j=0; j<MAXG; j++) {
      for (int k=0; k<MAXT; k++) {
        dp[j][k] = 0;
      }
    }
  }

  for (int l=1; l<=C; l++) {
    dp[1][d[l]*w[1]+FIX]++;
  }

  for (int i=2; i<=G; i++) {
    for (int j=i; j>=1; j--) {
      for (int k=MAXT-1; k>=0; k--) {
        for (int l=1; l<=C; l++) {
          if (k >= d[l]*w[i]) {
            if (dp[j-1][k-d[l]*w[i]] && dp[j][k]) {
              dp[j][k] += dp[j-1][k-d[l]*w[i]];
            } else if (dp[j][k] == 0) {
              dp[j][k] = dp[j-1][k-d[l]*w[i]];
            }
          }
        }
      }
    }
  }

  cout << dp[G][FIX] << endl;

  return 0;
}
