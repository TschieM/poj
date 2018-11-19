/*
Description

Chosen Problem Solving and Program design as an optional course, you are required
to solve all kinds of problems. Here, we get a new problem.

There is a very long board with length L centimeter, L is a positive integer, so
we can evenly divide the board into L segments, and they are labeled by 1, 2, ... L
from left to right, each is 1 centimeter long. Now we have to color the board -
one segment with only one color. We can do following two operations on the board:

1. "C A B C" Color the board from segment A to segment B with color C.
2. "P A B" Output the number of different colors painted between segment A and
segment B (including).

In our daily life, we have very few words to describe a color (red, green, blue,
yellow…), so you may assume that the total number of different colors T is very
small. To make it simple, we express the names of colors as color 1, color 2, ...
color T. At the beginning, the board was painted in color 1. Now the rest of problem
is left to your.

Input:
First line of input contains L (1 <= L <= 100000), T (1 <= T <= 30) and O
(1 <= O <= 100000). Here O denotes the number of operations. Following O lines,
each contains "C A B C" or "P A B" (here A, B, C are integers, and A may be larger
than B) as an operation defined previously.

Output:
Ouput results of the output operation in order, each line contains a number.

Sample Input:
2 2 4
C 1 1 2
P 1 2
C 2 2 2
P 1 2

Sample Output:
2
1
*/

#include <iostream>

#define MAXL 100100

using namespace std;

void update(int node, int ql, int qr, int col, int l, int r);
int query(int node, int ql, int qr, int l, int r);
int popcnt(int val);

int L, T, O, A, B, C;
int board[MAXL<<2], lazy[MAXL<<2];
char cmd;

int main() {
  std::ios::sync_with_stdio(false);
  for (int i=0; i<(MAXL<<2); i++) {
    board[i] = 1;
    lazy[i] = 0;
  }

  cin >> L >> T >> O;
  while (O--) {
    cin >> cmd;
    if (cmd == 'C') {
      cin >> A >> B >> C;
      update(1, min(A, B), max(A, B), C, 1, L);
    } else { // cmd = 'P'
      cin >> A >> B;
      cout << popcnt(query(1, min(A, B), max(A, B), 1, L)) << endl;
    }
  }

  return 0;
}

void update(int node, int ql, int qr, int col, int l, int r) {
  if (lazy[node]) {
    board[node] = lazy[node];
    if (l != r) {
      lazy[node<<1] = board[node];
      lazy[node<<1|1] = board[node];
    }
    lazy[node] = 0;
  }
  if (ql>r || qr<l) return ;
  if (ql<=l && qr>=r) {
    board[node] = (1 << (col-1));
    if (l != r) {
      lazy[node<<1] = board[node];
      lazy[node<<1|1] = board[node];
    }
    return ;
  }
  int mid = (l+r) >> 1;
  update(node<<1, ql, qr, col, l, mid);
  update(node<<1|1, ql, qr, col, mid+1, r);
  board[node] = board[node<<1] | board[node<<1|1];
}

int query(int node, int ql, int qr, int l, int r) {
  if (lazy[node]) {
    board[node] = lazy[node];
    if (l != r) {
      lazy[node<<1] = board[node];
      lazy[node<<1|1] = board[node];
    }
    lazy[node] = 0;
  }
  if (ql>r || qr<l) return 0;
  if (ql<=l && qr>=r) return board[node];
  int mid = (l+r) >> 1;
  return query(node<<1, ql, qr, l, mid) | query(node<<1|1, ql, qr, mid+1, r);
}

int popcnt(int val) {
  int cnt = 0;
  while (val) {
    if (val & 1) cnt++;
    val >>= 1;
  }
  return cnt;
}
