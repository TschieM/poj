#include <iostream>
#include <cmath>

using namespace std;

struct node {
  int key, val, depth;
  int lson, rson;
} tree[20000000];

int getDepth(int idx);
int insert(int idx, int key, int val);
int remove(int idx, int val);
int getPred(int idx);
int getMax(int idx);
int getMin(int idx);
int maintain(int idx);
int getBalance(int idx);
int leftRotate(int idx);
int rightRotate(int idx);

int root = 0, cnt = 0;

int main() {
  std::ios::sync_with_stdio(false);
  int cmd, K, P;
  while (cin>>cmd && cmd) {
    switch (cmd) {
      case 1:
        cin >> K >> P;
        root = insert(root, K, P);
        break;
      case 2:
        P = getMax(root);
        root = remove(root, P);
        break;
      case 3:
        P = getMin(root);
        root = remove(root, P);
        break;
    }
  }
  return 0;
}

int getDepth(int idx) {
  if (idx == 0) return 0;
  return tree[idx].depth;
}

int insert(int idx, int key, int val) {
  if (idx == 0) {
    idx = ++cnt;
    tree[idx].key = key;
    tree[idx].val = val;
    tree[idx].depth = 1;
    tree[idx].lson = tree[idx].rson = 0;
  } else if (val < tree[idx].val) {
    tree[idx].lson = insert(tree[idx].lson, key, val);
  } else if (val > tree[idx].val) {
    tree[idx].rson = insert(tree[idx].rson, key, val);
  }
  tree[idx].depth = max(getDepth(tree[idx].lson), getDepth(tree[idx].rson)) + 1;
  return maintain(idx);
}

int remove(int idx, int val) {
  if (idx == 0) return 0;
  if (val < tree[idx].val) tree[idx].lson = remove(tree[idx].lson, val);
  else if (val > tree[idx].val) tree[idx].rson = remove(tree[idx].rson, val);
  else {
    if (tree[idx].lson==0 && tree[idx].rson==0) idx = 0;
    else if (tree[idx].lson!=0 && tree[idx].rson==0) idx = tree[idx].lson;
    else if (tree[idx].lson==0 && tree[idx].rson!=0) idx = tree[idx].rson;
    else idx = getPred(tree[idx].lson);
  }
  tree[idx].depth = max(getDepth(tree[idx].lson), getDepth(tree[idx].rson)) + 1;
  return idx;
}

int getPred(int idx) {
  if (tree[idx].lson==0 && tree[idx].rson==0) return idx;
  return getPred(tree[idx].rson);
}

int getMax(int idx) {
  if (idx!=0 && tree[idx].rson!=0) return getMax(tree[idx].rson);
  if (idx == 0) cout << "0" << endl;
  else if (tree[idx].rson == 0) cout << tree[idx].key << endl;
  return tree[idx].val;
}

int getMin(int idx) {
  if (idx!=0 && tree[idx].lson!=0) return getMin(tree[idx].lson);
  if (idx == 0) cout << "0" << endl;
  else if (tree[idx].lson == 0) cout << tree[idx].key << endl;
  return tree[idx].val;
}

int maintain(int idx) {
  if (getBalance(idx)>=-1 && getBalance(idx)<=1) return idx;
  if (getBalance(idx) < -1) {
    if (getBalance(tree[idx].rson) >= 1) {
      tree[idx].rson = rightRotate(tree[idx].rson);
    }
    idx = leftRotate(idx);
  } else {
    if (getBalance(tree[idx].rson) <= -1) {
      tree[idx].lson = leftRotate(tree[idx].lson);
    }
    idx = rightRotate(idx);
  }
  return maintain(idx);
}

int getBalance(int idx) {
  if (idx == 0) return 0;
  return getDepth(tree[idx].lson) - getDepth(tree[idx].rson);
}

int leftRotate(int idx) {
  int temp = tree[idx].rson;
  tree[idx].rson = tree[temp].lson;
  tree[temp].lson = idx;
  tree[idx].depth = max(getDepth(tree[idx].lson), getDepth(tree[idx].rson)) + 1;
  tree[temp].depth = max(getDepth(tree[temp].lson), getDepth(tree[temp].rson)) + 1;
  return temp;
}

int rightRotate(int idx) {
  int temp = tree[idx].lson;
  tree[idx].lson = tree[temp].rson;
  tree[temp].rson = idx;
  tree[idx].depth = max(getDepth(tree[idx].lson), getDepth(tree[idx].rson)) + 1;
  tree[temp].depth = max(getDepth(tree[temp].lson), getDepth(tree[temp].rson)) + 1;
  return temp;
}
