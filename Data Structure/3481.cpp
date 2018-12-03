/*
Description
The new founded Balkan Investment Group Bank (BIG-Bank) opened a new office in
Bucharest, equipped with a modern computing environment provided by IBM Romania,
and using modern information technologies. As usual, each client of the bank is
identified by a positive integer K and, upon arriving to the bank for some
services, he or she receives a positive integer priority P. One of the inventions
of the young managers of the bank shocked the software engineer of the serving
system. They proposed to break the tradition by sometimes calling the serving
desk with the lowest priority instead of that with the highest priority. Thus,
the system will receive the following types of request:

---------------------------------------------------------------------------------
0	     |  The system needs to stop serving
---------------------------------------------------------------------------------
1 K P	 |  Add client K to the waiting list with priority P
---------------------------------------------------------------------------------
2	     |  Serve the client with the highest priority and drop him or her from
       |  the waiting list
---------------------------------------------------------------------------------
3	     |  Serve the client with the lowest priority and drop him or her from the
       |  waiting list
---------------------------------------------------------------------------------

Your task is to help the software engineer of the bank by writing a program to
implement the requested serving policy.

Input
Each line of the input contains one of the possible requests; only the last line
contains the stop-request (code 0). You may assume that when there is a request
to include a new client in the list (code 1), there is no other request in the
list of the same client or with the same priority. An identifier K is always less
than 106, and a priority P is less than 107. The client may arrive for being
served multiple times, and each time may obtain a different priority.

Output
For each request with code 2 or 3, the program has to print, in a separate line
of the standard output, the identifier of the served client. If the request
arrives when the waiting list is empty, then the program prints zero (0) to the
output.

Sample Input
2
1 20 14
1 30 3
2
1 10 99
3
2
2
0

Sample Output
0
20
30
10
0
*/

#include <iostream>
#include <cmath>

using namespace std;

struct node {
  int key, val, size;
  node* lson;
  node* rson;
};

node* insert(node* root, int key, int val);
node* remove(node* root, int val);
node* getPred(node* root);
node* maintain(node* root);
node* leftRotate(node* root);
node* rightRotate(node* root);
int getBalance(node* root);
int getMax(node* root);
int getMin(node* root);
int getSize(node* root);

int main() {
  std::ios::sync_with_stdio(false);
  node* root = NULL;
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

node* insert(node* root, int key, int val) {
  if (root == NULL) {
    root = new node;
    root->key = key;
    root->val = val;
    root->size = 1;
    root->lson = root->rson = NULL;
  }
  else if (val < root->val) root->lson = insert(root->lson, key, val);
  else if (val > root->val) root->rson = insert(root->rson, key, val);
  root->size = max(getSize(root->lson), getSize(root->rson)) + 1;
  return maintain(root);
}

node* remove(node* root, int val) {
  if (root == NULL) return root;
  if (val > root->val) root->rson = remove(root->rson, val);
  else if (val < root->val) root->lson = remove(root->lson, val);
  else {
    if (root->lson==NULL && root->rson==NULL) return NULL;
    else if (root->lson!=NULL && root->rson==NULL) root = root->lson;
    else if (root->lson==NULL && root->rson!=NULL) root = root->rson;
    else {
      node* temp = getPred(root->lson);
      temp->lson = root->lson;
      temp->rson = root->rson;
      root = temp;
    }
  }
  root->size = max(getSize(root->lson), getSize(root->rson)) + 1;
  return maintain(root);
}

node* getPred(node* root) {
  if (root==NULL || root->rson==NULL) return root;
  return getPred(root->rson);
}

int getMax(node* root) {
  if (root == NULL) {
    cout << "0" << endl;
    return 0;
  }
  if (root->rson == NULL) {
    cout << root->key << endl;
    return root->val;
  }
  return getMax(root->rson);
}

int getMin(node* root) {
  if (root == NULL) {
    cout << "0" << endl;
    return 0;
  }
  if (root->lson == NULL) {
    cout << root->key << endl;
    return root->val;
  }
  return getMin(root->lson);
}

node* maintain(node* root) {
  if (getBalance(root)>=-1 && getBalance(root)<=1) return root;
  if (getBalance(root) < -1) {
    if (getBalance(root->rson) >= 1) {
      root->rson = rightRotate(root->rson);
    }
    root = leftRotate(root);
  }
  if (getBalance(root) > 1) {
    if (getBalance(root->lson) <= -1) {
      root->lson = leftRotate(root->lson);
    }
    root = rightRotate(root);
  }
  return maintain(root);
}

int getBalance(node* root) {
  if (root==NULL) return 0;
  return getSize(root->lson) - getSize(root->rson);
}

node* leftRotate(node* root) {
  node* temp = root->rson;
  root->rson = temp->lson;
  temp->lson = root;
  root->size = max(getSize(root->lson), getSize(root->rson)) + 1;
  temp->size = max(getSize(temp->lson), getSize(temp->rson)) + 1;
  return temp;
}

node* rightRotate(node* root) {
  node* temp = root->lson;
  root->lson = temp->rson;
  temp->rson = root;
  root->size = max(getSize(root->lson), getSize(root->rson)) + 1;
  temp->size = max(getSize(temp->lson), getSize(temp->rson)) + 1;
  return temp;
}

int getSize(node* root) {
  if (root == NULL) return 0;
  return root->size;
}
