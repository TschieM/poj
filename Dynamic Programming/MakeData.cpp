#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

/* for 2374
int main()
{
	srand((unsigned) time(0));
	int N = (rand() % 50000) + 1;
  int S = (rand() % 200001) - 100000;
	cout << N << " " << S << endl;

  int ll, rl;
  for (int j=0; j<N; j++) {
    if (j == N-1) {
      ll = (rand() % (S+100001)) - 100000;
      rl = (rand() % (100001-S)) + S;
    }
    else {
      ll = (rand() % 200001) - 100000;
      rl = (rand() % (100001-ll)) + ll;
    }
    cout << ll << " " << rl << endl;
  }
	return 0;
}
*/


/* for 1170
int main() {
  srand((unsigned) time(0));
  int b = (rand() % 4) + 2;
  cout << b << endl;

  int c[10], k[10], p[10];
  for (int i=1; i<=b; i++) {
    c[i] = (rand() % 999) + 1;
    k[i] = (rand() % 5) + 1;
    p[i] = (rand() % 999) + 1;
    cout << c[i] << " " << k[i] << " " << p[i] << endl;
  }

  int s = (rand() % 99) + 1;
  cout << s << endl;
  int n, num, sump=0;
  int idx[b+1];
  for (int i=1; i<=b; i++) {
    idx[i] = i;
  }
  for (int i=1; i<=s; i++) {
    n = (rand() % b) + 1;
    cout << n << " ";
    for (int j=b; j>=1; j--) {
      swap(idx[j], idx[(rand()%j) + 1]);
    }
    sump = 0;
    for (int j=1; j<=n; j++) {
      num = (rand() % k[idx[j]]) + 1;
      sump += num*p[idx[j]];
      cout << c[idx[j]] << " " << num << " ";
    }
    cout << (rand() % sump) + 1 << endl;
  }

  return 0;
}
*/

// for 1015
int main() {
  srand((unsigned) time(0));
  int n = (rand()%201) + 1;
  // int n = 200;
  int m = (rand()%min(20,n)) + 1;
  cout << n << " " << m << endl;
  for (int i=1; i<=n; i++) {
    int p = (rand()%20);
    int d = (rand()%20);
    cout << p << " " << d << endl;
  }
  cout << 0 << " " << 0 << endl;

  return 0;
}
