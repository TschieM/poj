/*
Description

A single positive integer i is given. Write a program to find the digit located
in the position i in the sequence of number groups S1S2...Sk. Each group Sk consists
of a sequence of positive integer numbers ranging from 1 to k, written one after
another.

For example, the first 80 digits of the sequence are as follows:
11212312341234512345612345671234567812345678912345678910123 456789101112345678910

Input

The first line of the input file contains a single integer t (1 ≤ t ≤ 10), the number
of test cases, followed by one line for each test case. The line for a test case
contains the single integer i (1 ≤ i ≤ 2147483647)

Output

There should be one output line per test case containing the digit located in the
position i.

Sample Input

2
8
3

Sample Output

2
2
*/

#include <iostream>
#include <cmath>

using namespace std;

int n, i;
long long dp[40000];

int main() {
  dp[1] = 1;
  for (int j=1; j<=40000; j++) {
    int num = (int)log10((double)j) + 1;
    dp[j] = dp[j-1];
    if (num == 1) {
      dp[j] += j;
    }
    else {
      for (int k=2; k<=num; k++){
        dp[j] += 9*pow(10, k-2)*(k-1);
      }
      dp[j] += (j+1-pow(10, num-1))*num;
    }
  }

  cin >> n;
  while (n--) {
    cin >> i;
    if (i == 1) {
      cout << "1" << endl;
      continue;
    }
    for (int j=1; j<=39999; j++) {
      if (dp[j]<i && i<=dp[j+1]) {
        int cnt = i - dp[j];
        int k, len = 0;
        for(k=1; len<cnt; k++)
        {
            len += (int)log10((double)k) + 1;
        }
        cout << (k-1)/(int)pow((double)10,len-cnt)%10 << endl;
      }
    }
  }

  return 0;
}
