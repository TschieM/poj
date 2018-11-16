/*
Description

The citizens of Bytetown, AB, could not stand that the candidates in the mayoral
election campaign have been placing their electoral posters at all places at their
whim. The city council has finally decided to build an electoral wall for placing
the posters and introduce the following rules:

~ Every candidate can place exactly one poster on the wall.
~ All posters are of the same height equal to the height of the wall; the width of
a poster can be any integer number of bytes (byte is the unit of length in Bytetown).
~ The wall is divided into segments and the width of each segment is one byte.
~ Each poster must completely cover a continuous number of wall segments.

They have built a wall 10000000 bytes long (such that there is enough place for
all candidates). When the electoral campaign was restarted, the candidates were
placing their posters on the wall and their posters differed widely in width.
Moreover, the candidates started placing their posters on wall segments already
occupied by other posters. Everyone in Bytetown was curious whose posters will be
visible (entirely or in part) on the last day before elections.

Your task is to find the number of visible posters when all the posters are placed
given the information about posters' size, their place and order of placement on
the electoral wall.

Input

The first line of input contains a number c giving the number of cases that follow.
The first line of data for a single case contains number 1 <= n <= 10000. The
subsequent n lines describe the posters in the order in which they were placed.
The i-th line among the n lines contains two integer numbers li and ri which are
the number of the wall segment occupied by the left end and the right end of the
i-th poster, respectively. We know that for each 1 <= i <= n, 1 <= li <= ri <= 10000000.
After the i-th poster is placed, it entirely covers all wall segments numbered
li, li+1 ,... , ri.

Output

For each input data set print the number of visible posters after all the posters
are placed.

Sample Input                              Sample Output
1                                         4
5
1 4
2 6
8 10
3 4
7 10
*/

#include <iostream>
#include <algorithm>

#define MAXN 40010

using namespace std;

void update(int node, int ql, int qr, int val, int l, int r);
void query(int node, int ql, int qr, int l, int r);
bool fcmp(int i, int j);

int C, N, nump;
int ar[MAXN], idx[MAXN], dis[MAXN<<1];
int tree[MAXN<<3], lazy[MAXN<<3], cnt[MAXN<<3];
bool mark[MAXN<<1];

int main() {
  cin >> C;
  while(C--) {
    for (int i=0; i<(MAXN<<3); i++) {
      if (i < (MAXN<<1)) mark[i] = false;
      tree[i] = 0;
      lazy[i] = 0;
      cnt[i] = 0;
    }
    cin >> N;
    // 数据离散化
    for (int i=1; i<=N; i++) {
      cin >> ar[(i<<1)-1] >> ar[i<<1];
      idx[(i<<1)-1] = (i<<1)-1;
      idx[i<<1] = (i<<1);
    }
    sort(idx+1, idx+(N<<1)+1, fcmp);
    for (int i=1; i<=(N<<1); i++) {
      if (i == 1) dis[idx[1]] = 1;
      else dis[idx[i]] = dis[idx[i-1]] +
                    ((ar[idx[i]]-ar[idx[i-1]]<=1)?(ar[idx[i]]-ar[idx[i-1]]):2);
    }
    // 区间跟新线段树tree
    for (int i=1; i<=N; i++) {
      update(1, dis[(i<<1)-1], dis[i<<1], i, 1, MAXN);
    }
    // 查询tree有多少个不同的数
    nump = 0;
    query(1, 1, MAXN<<1, 1, MAXN<<1);
    cout << nump << endl;
  }
  return 0;
}

void update(int node, int ql, int qr, int val, int l, int r) {
  if (ql>r || qr<l) return ;
  if (lazy[node]) {
    tree[node] = lazy[node];
    lazy[node<<1] = tree[node];
    lazy[node<<1|1] = tree[node];
    lazy[node] = 0;
  }
  if (ql<=l && qr>=r) {
    tree[node] = val;
    lazy[node<<1] = tree[node];
    lazy[node<<1|1] = tree[node];
    return ;
  }
  int mid = (l+r) >> 1;
  update(node<<1, ql, qr, val, l, mid);
  update(node<<1|1, ql, qr, val, mid+1, r);
}

void query(int node, int ql, int qr, int l, int r){
  if (ql>r || qr<l) return ;
  if (lazy[node]) {
    tree[node] = lazy[node];
    lazy[node<<1] = tree[node];
    lazy[node<<1|1] = tree[node];
    lazy[node] = 0;
  }
  if (l == r) {
    if (!mark[tree[node]] && tree[node]) {
      nump++;
      mark[tree[node]] = true;
    }
    return ;
  }
  int mid = (l+r) >> 1;
  query(node<<1, ql, qr, l, mid);
  query(node<<1|1, ql, qr, mid+1, r);
}

bool fcmp(int i, int j) {
  return ar[i] < ar[j];
}
