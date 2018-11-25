/*
Description

Railway tickets were difficult to buy around the Lunar New Year in China, so we
must get up early and join a long queue… The Lunar New Year was approaching, but
unluckily the Little Cat still had schedules going here and there. Now, he had to
travel by train to Mianyang, Sichuan Province for the winter camp selection of
the national team of Olympiad in Informatics. It was one o’clock a.m. and dark
outside. Chill wind from the northwest did not scare off the people in the queue.
The cold night gave the Little Cat a shiver. Why not find a problem to think
about? That was none the less better than freezing to death!

People kept jumping the queue. Since it was too dark around, such moves would not
be discovered even by the people adjacent to the queue-jumpers. “If every person
in the queue is assigned an integral value and all the information about those who
have jumped the queue and where they stand after queue-jumping is given, can I find
out the final order of people in the queue?” Thought the Little Cat.

Input

There will be several test cases in the input. Each test case consists of N + 1
lines where N (1 ≤ N ≤ 200,000) is given in the first line of the test case. The
next N lines contain the pairs of values Posi and Vali in the increasing order of
i (1 ≤ i ≤ N). For each i, the ranges and meanings of Posi and Vali are as follows:

Posi ∈ [0, i − 1] — The i-th person came to the queue and stood right behind the
Posi-th person in the queue. The booking office was considered the 0th person and
the person at the front of the queue was considered the first person in the queue.
Vali ∈ [0, 32767] — The i-th person was assigned the value Vali.

There no blank lines between test cases. Proceed to the end of input.

Output

For each test cases, output a single line of space-separated integers which are
the values of people in the order they stand in the queue.

Sample Input:
4
0 77
1 51
1 33
2 69
4
0 20523
1 19243
1 3890
0 31492

Sample Output:
77 33 69 51
31492 20523 3890 19243
*/

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 200100

void construct(int node, int l, int r);
void update(int node, int val, int l, int r);
int query(int node, int val, int l, int r);

int N;
int pos[MAXN], arr[MAXN], queue[MAXN], tree[MAXN<<2];

int main() {
  std::ios::sync_with_stdio(false);
  while (cin >> N) {
    construct(1, 1, N);
    for (int i=0; i<N; i++) {
      cin >> pos[i] >> arr[i];
    }

    for (int i=N-1; i>=0; i--) {
      int posi = query(1, pos[i]+1, 1, N);
      queue[posi] = arr[i];
      update(1, posi, 1, N);
    }
    for (int i=1; i<=N; i++) cout << queue[i] << " ";
    cout << endl;
  }
  return 0;
}

void construct(int node, int l, int r) {
  if (l > r) return ;
  if (l == r) {
    tree[node] = 1;
    return ;
  }
  int mid = (l+r) >> 1;
  construct(node<<1, l, mid);
  construct(node<<1|1, mid+1, r);
  tree[node] = tree[node<<1] + tree[node<<1|1];
}

void update(int node, int val, int l, int r) {
  if (val>r || val<l || l>r) return ;
  if (l == r) {
    tree[node] = 0;
    return ;
  }
  int mid = (l+r) >> 1;
  update(node<<1, val, l, mid);
  update(node<<1|1, val, mid+1, r);
  tree[node] = tree[node<<1] + tree[node<<1|1];
}

int query(int node, int val, int l, int r) {
  if (l == r) {
    return l;
  }
  int mid = (l+r) / 2;
  if (tree[node<<1] >= val) return query(node<<1, val, l, mid);
  return query(node<<1|1, val-tree[node<<1], mid+1, r);
}
