/*
Description

In this problem, you have to analyze a particular sorting algorithm. The algorithm
processes a sequence of n distinct integers by swapping two adjacent sequence
elements until the sequence is sorted in ascending order. For the input sequence
9 1 0 5 4 ,

Ultra-QuickSort produces the output
0 1 4 5 9 .

Your task is to determine how many swap operations Ultra-QuickSort needs to perform
in order to sort a given input sequence.

Input

The input contains several test cases. Every test case begins with a line that
contains a single integer n < 500,000 -- the length of the input sequence. Each
of the the following n lines contains a single integer 0 ≤ a[i] ≤ 999,999,999, the
i-th input sequence element. Input is terminated by a sequence of length n = 0.
This sequence must not be processed.

Output

For every input sequence, your program prints a single line containing an integer
number op, the minimum number of swap operations necessary to sort the given input
sequence.

Sample Input
5
9 1 0 5 4
3
1 2 3
0

Sample Output
6
0
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 600000

void update(int node, int val, int l, int r);
long long query(int node, int ql, int qr, int l, int r);

int n, arr[MAXN], idx[MAXN], narr[MAXN], tree[MAXN<<2];
long long swapN = 0;

int main() {
  while (cin>>n && n) {
    swapN = 0;
    for (int i=1; i<=n; i++) {
      scanf("%d", &arr[i]);
      idx[i] = i;
      narr[i] = i;
    }

    for (int i=0; i<(n<<2); i++) {
      tree[i] = 0;
    }

    sort(idx+1, idx+n+1, [](int i, int j){return arr[i]<arr[j];});
    sort(narr+1, narr+n+1, [](int i, int j){return idx[i]<idx[j];});

    for (int i=1; i<=n; i++) {
      swapN += i - 1 - query(1, 1, narr[i], 1, n);
      update(1, narr[i], 1, n);
    }

    cout << swapN << endl;
  }

  return 0;
}

void update(int node, int val, int l, int r) {
  if (l == r) {
    tree[node] = 1;
    return ;
  }
  int mid = (l+r) >> 1;
  if (val <= mid) {
    update(node<<1, val, l, mid);
  } else {
    update((node<<1)+1, val, mid+1, r);
  }
  tree[node] = tree[node<<1] + tree[(node<<1)+1];
}

long long query(int node, int ql, int qr, int l, int r) {
  if (qr<l || ql>r) {
    return 0;
  }
  if (ql<=l && qr>=r) {
    return tree[node];
  }
  int mid = (l+r) >> 1;
  return query(node<<1, ql, qr, l, mid) + query((node<<1)+1, ql, qr, mid+1, r);
}

/*  无序离散化
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 600000

void construct(int node, int l, int r);
long long query(int node, int ql, int qr, int l, int r);
bool fcomp(int i, int j);

int n, arr[MAXN], idx[MAXN], tree[MAXN<<2];
long long swapN = 0;

int main() {
  while (cin>>n && n) {
    swapN = 0;
    for (int i=1; i<=n; i++) {
      scanf("%d", &arr[i]);
      idx[i] = i;
    }

    construct(1, 1, n);

    sort(idx+1, idx+n+1, fcomp);

    for (int i=1; i<=n; i++) {
      swapN += query(1, 1, idx[i], 1, n);
    }

    cout << swapN << endl;
  }

  return 0;
}

void construct(int node, int l, int r) {
  if (l == r) {
    tree[node] = 1;
    return ;
  }
  int mid = (l+r) >> 1;
  construct(node<<1, l, mid);
  construct((node<<1)+1, mid+1, r);
  tree[node] = tree[node<<1] + tree[(node<<1)+1];
}

long long query(int node, int ql, int qr, int l, int r) {
  if (qr<l || ql>r) {
    return 0;
  }
  if (ql<=l && qr>=r) {
    if (qr == r) {
      for (int i=node; i>0; i>>=1) {
        tree[i]--;
      }
    }
    return tree[node]>0 ? tree[node]:0;
  }
  int mid = (l+r) >> 1;
  return query(node<<1, ql, qr, l, mid) + query((node<<1)+1, ql, qr, mid+1, r);
}

bool fcomp(int i, int j) {
  return arr[i] < arr[j];
}
*/
