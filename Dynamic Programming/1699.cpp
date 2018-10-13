/*
Description

The twenty-first century is a biology-technology developing century. One of the
most attractive and challenging tasks is on the gene project, especially on gene
sorting program. Recently we know that a gene is made of DNA. The nucleotide bases
from which DNA is built are A(adenine), C(cytosine), G(guanine), and T(thymine).
Given several segments of a gene, you are asked to make a shortest sequence from
them. The sequence should use all the segments, and you cannot flip any of the
segments.

For example, given 'TCGG', 'GCAG', 'CCGC', 'GATC' and 'ATCG', you can slide the
segments in the following way and get a sequence of length 11. It is the shortest
sequence (but may be not the only one).

Input

The first line is an integer T (1 <= T <= 20), which shows the number of the cases.
Then T test cases follow. The first line of every test case contains an integer
N (1 <= N <= 10), which represents the number of segments. The following N lines
express N segments, respectively. Assuming that the length of any segment is between
1 and 20.

Output

For each test case, print a line containing the length of the shortest sequence
that can be made from these segments.

Sample Input                        Sample Output

1                                   11
5
TCGG
GCAG
CCGC
GATC
ATCG
*/

#include <iostream>
#include <string>

using namespace std;

int T, N, POW;
string seg[15];
int segLen = 300;
int s[15][1000];
int dp[1030][15];
int w[15][15];

int popcount(int x);
int addLen(int a, int b);

int main(){
  cin >> T;

  while(T--){
    segLen = 300;
    cin >> N;
    POW = (1<<N)-1; 
    for(int i=1; i<=N; i++) cin >> seg[i];

    for(int i=0; i<=N; i++) s[i][0] = 0;
    for(int i=0; i<=POW; i++){
      int n = popcount(i);
      s[n][++s[n][0]] = i;
    }

    for(int i=1; i<=POW; i++){
      for(int j=1; j<=N; j++){
        dp[i][j] = 300;
      }
    }

    for(int i=1; i<=N; i++){
      for(int j=1; j<=N; j++){
        w[i][j] = addLen(i, j);
      }
    }

    for(int i=1; i<=N; i++){
      for(int j=1; j<=s[i][0]; j++){
        if(i==1) dp[s[i][j]][j] = seg[j].length();
        else{
          for(int k=0; k<N; k++){
            if((s[i][j]>>k)&1){
              int x = (1<<k);
              for(int l=1; l<=N; l++){
                dp[s[i][j]][k+1] = min(dp[s[i][j]][k+1], dp[s[i][j]-x][l]+w[l][k+1]);
              }
            }
          }
        }
      }
    }

    for(int i=1; i<=N; i++) segLen = min(segLen, dp[POW][i]);
    cout << segLen << endl;
  }

  return 0;
}

int popcount(int x) {
    int cnt = 0;
    while (x) ++cnt, x -= (x&-x);
    return cnt;
}

int addLen(int a, int b) {
    int lena = seg[a].length(), lenb = seg[b].length();

    for (int j=lenb; j>0; j--) {
        if (lena >= j && seg[a].substr(lena-j, j) == seg[b].substr(0, j))
            return lenb - j;
    }

    return lenb;
}
