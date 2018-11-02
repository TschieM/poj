
#include <iostream>
#include <cmath>

using namespace std;

#define INF 0x7fffffff

void construct(int i, int left, int right);
void update(int i, int value, int j, int left, int right);
void update_range(int left, int right, int value, int i, int l, int r);
void update_rangex2(int left, int right, int i, int l, int r);
int query(int i, int l, int r, int left, int right);

int n;
int tree[1000];
int lazy[1000];
int arr[300];

int main() {
  cin >> n;
  for (int i=1; i<=n; i++) {
    cin >> arr[i];
  }
  construct(1, 1, n);
  int left, right, idx, value;
  while (cin >> left >> right){
    cout << "the minimal element in the given range is: " << endl;
    cout << query(1, 1, n, left, right) << endl;
    for (int i=0; i<1000; i++) {
      lazy[i] = 0;
    }
    // cout << "the index and value of changed element: " << endl;
    // cin >> idx >> value;
    // update(idx, value, 1, 1, n);
    // update_range(2, 3, 1, 1, 1, n);
    update_rangex2(2, 4, 1, 1, n);
  }

  return 0;
}

void construct(int i, int l, int r) {
  if (l == r) {
    tree[i] = arr[l];
  }
  if (l < r) {
    int mid = (l+r) / 2;
    construct(2*i, l, mid);
    construct(2*i+1, mid+1, r);
    tree[i] = min(tree[2*i], tree[2*i+1]);
  }
}

void update(int i, int value, int j, int l, int r) {
  if (l == r) {
    arr[i] = value;
    tree[j] = value;
  }
  if (l < r) {
    int mid = (l+r) / 2;
    if (l<=i && i<=mid) {
      update(i, value, 2*j, l, mid);
    }
    if (mid<i && i<=r) {
      update(i, value, 2*j+1, mid+1, r);
    }
    tree[j] = min(tree[2*j], tree[2*j+1]);
  }
}

void update_range(int left, int right, int value, int i, int l, int r) {
  if (left>r || right<l) {
    return ;
  }
  if (left<=l && right>=r) {
    tree[i] = value;
    lazy[i] = 1;
    return ;
  }
  int mid = (l+r) / 2;
  update_range(left, right, value, 2*i, l, mid);
  update_range(left, right, value, 2*i+1, mid+1, r);
  tree[i] = min(tree[2*i], tree[2*i+1]);
}

void update_rangex2(int left, int right, int i, int l, int r) {
  if (left>r || right<l) {
    return ;
  }
  if (left<=l && right>=r) {
    tree[i] *= 2;
    lazy[i] = 1;
    return ;
  }
  int mid = (l+r) / 2;
  update_rangex2(left, right, 2*i, l, mid);
  update_rangex2(left, right, 2*i+1, mid+1, r);
  tree[i] = min(tree[2*i], tree[2*i+1]);
}

int query(int i, int l, int r, int left, int right) {
  if (lazy[i] == 1) {
    lazy[2*i] = 1;
    // tree[2*i] = tree[i];
    tree[2*i] *= 2;
    lazy[2*i+1] = 1;
    // tree[2*i+1] = tree[i];
    tree[2*i+1] *= 2;
  }
  if (left>r || right<l) {
    return INF;
  }
  if (left<=l && right>=r) {
    return tree[i];
  }
  int mid = (l+r) / 2;
  return min(query(2*i, l, mid, left, right), query(2*i+1, mid+1, r, left, right));
}
