/*
Description
We give the following inductive definition of a “regular brackets” sequence:
the empty sequence is a regular brackets sequence,
if s is a regular brackets sequence, then (s) and [s] are regular brackets sequences,
and if a and b are regular brackets sequences, then ab is a regular brackets sequence.
no other sequence is a regular brackets sequence
For instance, all of the following character sequences are regular brackets sequences:
(), [], (()), ()[], ()[()]
while the following character sequences are not:
(, ], )(, ([)], ([(]
Given a brackets sequence of characters a1a2 … an, your goal is to find the length
of the longest regular brackets sequence that is a subsequence of s. That is, you
wish to find the largest m such that for indices i1, i2, …, im where
1 ≤ i1 < i2 < … < im ≤ n, ai1ai2 … aim is a regular brackets sequence.
Given the initial sequence ([([]])], the longest regular brackets subsequence is
[([])].

Input
The input test file will contain multiple test cases. Each input test case consists
of a single line containing only the characters (, ), [, and ]; each input test will
have length between 1 and 100, inclusive. The end-of-file is marked by a line containing
the word “end” and should not be processed.

Output
For each input case, the program should print the length of the longest possible
regular brackets subsequence on a single line.

Sample Input    Sample Output
((()))          6
()()()          6
([]])           4
)[)(            0
([][][)         6
end
*/

#include <iostream>
#include <cstring>
#include <vector>

#define MAXN 10000

using namespace std;

vector<string> s;
string brackets;
int N, M;
int a[MAXN];
int f[MAXN][MAXN];

int main(){
  while(cin>>brackets && brackets!="end"){
    s.push_back(brackets);
  }
  M = s.size();

  for(int l=0;l<M;l++){
    N = s[l].length();
    for(int i=0;i<N;i++){
      switch (s[l][i]) {
        case '(': a[i+1] = 0; break;
        case ')': a[i+1] = 1; break;
        case '[': a[i+1] = 2; break;
        case ']': a[i+1] = 3; break;
      }
    }

    for(int i=0;i<=N;i++){
      for(int j=0;j<=N;j++){
        f[i][j] = 0;
      }
    }

    for(int j=1;j<N;j++){
      for(int i=1;i<=N-j;i++){
        if(a[i]<a[i+j] && (a[i]^a[i+j])==1){
          f[i][i+j] = f[i+1][i+j-1]+2;
        }
        for(int k=i;k<i+j;k++)
          f[i][i+j] = max(f[i][i+j], f[i][k]+f[k+1][i+j]);
      }
    }
    cout<<f[1][N]<<endl;
  }

  return 0;
}
