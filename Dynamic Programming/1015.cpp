/*
Description
In Frobnia, a far-away country, the verdicts in court trials are determined by a
jury consisting of members of the general public. Every time a trial is set to
begin, a jury has to be selected, which is done as follows. First, several people
are drawn randomly from the public. For each person in this pool, defence and
prosecution assign a grade from 0 to 20 indicating their preference for this person.
0 means total dislike, 20 on the other hand means that this person is considered
ideally suited for the jury.
Based on the grades of the two parties, the judge selects the jury. In order to
ensure a fair trial, the tendencies of the jury to favour either defence or
prosecution should be as balanced as possible. The jury therefore has to be chosen
in a way that is satisfactory to both parties.
We will now make this more precise: given a pool of n potential jurors and two
values di (the defence's value) and pi (the prosecution's value) for each potential
juror i, you are to select a jury of m persons. If J is a subset of {1,..., n} with
m elements, then D(J ) = sum(dk) k belong to J and P(J) = sum(pk) k belong to J
are the total values of this jury for defence and prosecution.
For an optimal jury J , the value |D(J) - P(J)| must be minimal. If there are several
jurys with minimal |D(J) - P(J)|, one which maximizes D(J) + P(J) should be selected
since the jury should be as ideal as possible for both parties.
You are to write a program that implements this jury selection process and chooses
an optimal jury given a set of candidates.
Input
The input file contains several jury selection rounds. Each round starts with a
line containing two integers n and m. n is the number of candidates and m the number
of jury members.
These values will satisfy 1<=n<=200, 1<=m<=20 and of course m<=n. The following n
lines contain the two integers pi and di for i = 1,...,n. A blank line separates
each round from the next.
The file ends with a round that has n = m = 0.
Output
For each round output a line containing the number of the jury selection round
('Jury #1', 'Jury #2', etc.). On the next line print the values D(J) and P (J)
of your jury as shown below and on another line print the numbers of the m chosen
candidates in ascending order. Output a blank before each individual candidate number.
Output an empty line after each test case.
Sample Input
4 2
1 2
2 3
4 1
6 2
0 0
Sample Output
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3
Hint
If your solution is based on an inefficient algorithm, it may not execute in the
allotted time.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool selected (int i, int j, int k);
void juryfill(int i, int j, bool select);
void jury_compare();


int n, m;
int p[205], d[205];
int f[25][805];
int path[25][805][2];
vector<int> jury, jury_bak;

int main() {
  int cnt = 0;
  // input
  while (cin>>n && n!=0 && cin>>m && m!=0) {
    jury.clear();
    for (int i=1; i<=n; i++) {
      cin >> p[i] >> d[i];
    }

    int mid = 20*m;
    for (int i=1; i<25; i++) {
      for (int j=0; j<805; j++) {
        path[i][j][0] = path[i][j][1] = 0;
        f[i][j] = -1;
      }
    }
    for (int i=1; i<=n; i++) {
      if (p[i]+d[i] > f[1][mid+p[i]-d[i]]) {
        f[1][mid+p[i]-d[i]] = p[i]+d[i];
        path[1][mid+p[i]-d[i]][1] = i;
      }
    }

    for (int i=2; i<=m; i++) {
      for (int j=0; j<=40*m; j++) {
        for (int k=1; k<=n; k++) {
          if (j>=p[k]-d[k] && !selected(i-1,j-p[k]+d[k],k) && f[i-1][j-p[k]+d[k]]!=-1) {
            if (f[i][j] < f[i-1][j-p[k]+d[k]]+p[k]+d[k]) {
              f[i][j] = f[i-1][j-p[k]+d[k]]+p[k]+d[k];
              path[i][j][0] = j-p[k]+d[k];
              path[i][j][1] = k;
            }
          }
        }
      }
    }

    // output
    int pout, dout;
    cout << "Jury #" << ++cnt << endl;
    for (int i=0; i<=20*m; i++) {
      if (f[m][mid-i] > f[m][mid+i]) {
        pout = (f[m][mid-i]-i)/2;
        dout = (f[m][mid-i]+i)/2;
        juryfill(m, mid-i, true);
        break;
      }
      if (f[m][mid-i] < f[m][mid+i]) {
        pout = (f[m][mid+i]+i)/2;
        dout = (f[m][mid+i]-i)/2;
        juryfill(m, mid+i, true);
        break;
      }
      if (f[m][mid-i]==f[m][mid+i] && f[m][mid-i]!=-1) {
        pout = (f[m][mid+i]+i)/2;
        dout = (f[m][mid+i]-i)/2;
        juryfill(m, mid+i, true);
        juryfill(m, mid-i, false);
        jury_compare();
        break;
      }
    }
    cout << "Best jury has value " << pout << " for prosecution ";
    cout << "and value " << dout << " for defence:" << endl;
    for (int i=0; i<m; i++) {
      cout << " " << jury[i];
    }
    cout << endl;
    cout << endl;
  // cout << abs(pout-dout) << " " << pout+dout << endl;
  }

  return 0;
}

bool selected(int i, int j, int k){
  while (path[i][j][1]) {
    if (path[i][j][1] == k) {
      return true;
    }
    j = path[i][j][0];
    i--;
  }
  return false;
}

void juryfill(int i, int j, bool select) {
  while (path[i][j][1]) {
    if (select) {
      jury.push_back(path[i][j][1]);
    }
    else {
      jury_bak.push_back(path[i][j][1]);
    }
    j = path[i][j][0];
    i--;
  }
  if (select) {
    sort(jury.begin(),jury.end());
  }
  else {
    sort(jury_bak.begin(),jury_bak.end());
  }
}

void jury_compare() {
  for (int i=0; i<jury.size(); i++) {
    if (jury_bak[i] < jury[i]) {
      jury = jury_bak;
      break;
    }
  }
}
