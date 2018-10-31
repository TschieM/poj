#include <iostream>

using namespace std;

#define INF 0x7fffffff
int query(int i, int l, int r, int left, int right);
void construct(int i, int left, int right);

int n;
int tree[1000];
int arr[300];

int main() {
  cin >> n;
  for (int i=1; i<=n; i++) {
    cin >> arr[i];
  }
  construct(1, 1, n);
  int l, r;
  bool flag;
  while (cin >> flag && flag){
    cin >> l >> r;
    cout << query(1, 1, n, l, r) << endl;
  }

  return 0;
}

int query(int i, int l, int r, int left, int right) {
  if (left>r || right<l) {
    return INF;
  }
  if (left<=l && right>=r) {
    return tree[i];
  }
  int mid = (l+r)/2;
  return min(query(2*i,l,mid,left,right), query(2*i+1,mid+1,r,left,right));
}

void construct(int i, int left, int right) {
  if (left==right) {
    tree[i] = arr[left];
  }
  if (left<right) {
    int mid = (left+right)/2;
    construct(2*i, left, mid);
    construct(2*i+1, mid+1, right);
    tree[i] = min(tree[2*i], tree[2*i+1]);
  }
}
