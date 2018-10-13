/*
Description:
There is a straight highway with villages alongside the highway. The highway is
represented as an integer axis, and the position of each village is identified with
a single integer coordinate. There are no two villages in the same position. The
distance between two positions is the absolute value of the difference of their
integer coordinates. Post offices will be built in some, but not necessarily all
of the villages. A village and the post office in it have the same position. For
building the post offices, their positions should be chosen so that the total sum
of all distances between each village and its nearest post office is minimum. You
are to write a program which, given the positions of the villages and the number
of post offices, computes the least possible sum of all distances between each
village and its nearest post office.

Input:
Your program is to read from standard input. The first line contains two integers:
the first is the number of villages V, 1 <= V <= 300, and the second is the number
of post offices P, 1 <= P <= 30, P <= V. The second line contains V integers in
increasing order. These V integers are the positions of the villages. For each
position X it holds that 1 <= X <= 10000.

Output:
The first line contains one integer S, which is the sum of all distances between
each village and its nearest post office.

Sample Input:
10 5
1 2 3 6 7 9 11 22 44 50

Sample Output:
9
*/

#include<iostream>

#define INF 0x7fffffff

using namespace std;

int N, P;
int v[305];
int f[305][35], w[305][305];

int gen_dist(int i){
  int dist = 0;
  for(int j=1;j<i;j++) dist += v[i]-v[j];
  return dist;
}

int main(){
  cin >> N >> P;
  for(int i=1; i<=N; i++){
    cin >> v[i];
    v[i+1] = INF;
  }

  for(int i=1; i<=N+1; i++){
    for(int j=1; j<=N+1; j++){
      w[i][j] = 0;
      for(int k=i+1; k<j; k++){
        w[i][j] += min(v[k]-v[i],v[j]-v[k]);
      }
    }
  }

  for(int i=1; i<=N+1; i++){
    for(int j=1; j<=P+1; j++){
      f[i][j] = INF;
      if(j>=i) f[i][j] = 0;
      if(j==1) f[i][j] = gen_dist(i);
      if(j<i && j>1){
        for(int k=1; k<i; k++){
          f[i][j] = min(f[i][j], f[k][j-1]+w[k][i]);
        }
      }
    }
  }

  cout<<f[N+1][P+1]<<endl;

  return 0;
}
