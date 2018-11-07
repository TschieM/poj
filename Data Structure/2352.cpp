/*
Description

Astronomers often examine star maps where stars are represented by points on a
plane and each star has Cartesian coordinates. Let the level of a star be an amount
of the stars that are not higher and not to the right of the given star. Astronomers
want to know the distribution of the levels of the stars.

For example, look at the map shown on the figure above. Level of the star number
5 is equal to 3 (it's formed by three stars with a numbers 1, 2 and 4). And the
levels of the stars numbered by 2 and 4 are 1. At this map there are only one star
of the level 0, two stars of the level 1, one star of the level 2, and one star
of the level 3.


                                      *(5)

                                  *(4)

                              * (1)   *(2)  *(3)

You are to write a program that will count the amounts of the stars of each level
on a given map.

Input

The first line of the input file contains a number of stars N (1<=N<=15000). The
following N lines describe coordinates of stars (two integers X and Y per line
separated by a space, 0<=X,Y<=32000). There can be only one star at one point of
the plane. Stars are listed in ascending order of Y coordinate. Stars with equal
Y coordinates are listed in ascending order of X coordinate.

Output

The output should contain N lines, one number per line. The first line contains
amount of stars of the level 0, the second does amount of stars of the level 1
and so on, the last line contains amount of stars of the level N-1.

Sample Input
5
1 1
5 1
7 1
3 3
5 5

Sample Output
1
2
1
1
0

Hint
This problem has huge input data,use scanf() instead of cin to read data to avoid
time limit exceed.
*/

#include <iostream>
#include <cstdio>

using namespace std;

#define MAXN 16000
#define MAXV 33000

void update(int node, int idx, int l, int r);
int query(int node, int ql, int qr, int l, int r);

int N;
int x[MAXN], y[MAXN], layer[MAXN], tree[MAXV<<2];

int main() {
  for (int i=1; i<(MAXV<<2); i++) {
    tree[i] = 0;
  }

  scanf("%d", &N);
  for (int i=1; i<=N; i++) {
    scanf("%d %d", &x[i], &y[i]);
    layer[query(1, 1, x[i]+1, 1, MAXV)]++;
    update(1, x[i]+1, 1, MAXV);
  }

  for (int i=0; i<N; i++) {
    cout << layer[i] << endl;
  }

  return 0;
}

void update(int node, int idx, int l, int r) {
  tree[node]++;
  if (l == r) {
    return ;
  }
  int mid = (l+r) >> 1;
  if (idx <= mid) {
    update(node<<1, idx, l, mid);
  }
  else {
    update((node<<1)+1, idx, mid+1, r);
  }
}

int query(int node, int ql, int qr, int l, int r) {
  if (ql>r || qr<l) {
    return 0;
  }
  if (ql<=l && qr>=r) {
    return tree[node];
  }
  int mid = (l+r) >> 1;
  return query(node<<1, ql, qr, l, mid) + query((node<<1)+1, ql, qr, mid+1, r);
}
