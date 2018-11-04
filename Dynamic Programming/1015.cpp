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
#include <cstdio>

using namespace std;

int n, m;
int p[201], d[201], sub[201], sum[201];
int f[21][801];
int path[21][801][21];
int jury[21];

int main() {
  int cnt = 0;
  // input
  while (cin>>n>>m && n && m) {
    int psum = 0, dsum = 0;
    for (int i=1; i<=n; i++) {
      cin >> p[i] >> d[i];
      sub[i] = p[i] - d[i];
      sum[i] = p[i] + d[i];
    }

    int fix = 20 * m;
    for (int j=0; j<=20; j++) {
      for (int k=0; k<=800; k++) {
        f[j][k] = (j==0 && k==fix)? 0:-9999999;
      }
    }

    for (int i=1; i<=n; i++) {
      for (int j=min(i,m); j>=1; j--) {
        for (int k=0; k<=800; k++) {
          if (k>=sub[i] && f[j-1][k-sub[i]]+sum[i]>f[j][k]) {
            f[j][k] = f[j-1][k-sub[i]]+sum[i];
            path[j][k][j] = i;
            for (int l=j-1; l>=1; l--) {
              path[j][k][l] = path[j-1][k-sub[i]][l];
            }
          }
        }
      }
    }

    for (int i=0; i<=20*m; i++) {
      int s = f[m][i+fix] >= f[m][-i+fix] ? i : -i;
      if (f[m][s+fix] < 0) {
        continue;
      }

      for (int j=m; j>0; j--) {
        jury[j] = path[m][s+fix][j];
        psum += p[jury[j]];
        dsum += d[jury[j]];
      }
      break;
    }

    printf("Jury #%d\n", ++cnt);
    printf("Best jury has value %d for prosecution and value %d for defence:\n", psum, dsum);
    for (int i=1; i<=m; i++)
        printf(" %d", jury[i]);
    printf("\n\n");
  }

  return 0;
}

// #include <iostream>
// #include <cstdio>
//
// using namespace std;
//
// int n, m;
// int p[201], d[201], sub[201], sum[201];
// int f[201][21][801]; // 前 i 个候选人 选取 j 个， p-d=k 时 p+d 的最大值
// int path[201][21][801][21];
// int jury[21];
//
// int main() {
//   int cnt = 0;
//   // input
//   while (cin>>n>>m && n && m) {
//     int psum = 0, dsum = 0;
//     for (int i=1; i<=n; i++) {
//       cin >> p[i] >> d[i];
//       sub[i] = p[i] - d[i];
//       sum[i] = p[i] + d[i];
//     }
//
//     int fix = 20 * m;
//     for (int i=0; i<=200; i++) {
//       for (int j=0; j<=20; j++) {
//         for (int k=0; k<=800; k++) {
//           f[i][j][k] = (j==0 && k==fix)? 0:-9999999;
//         }
//       }
//     }
//
//     for (int i=1; i<=n; i++) {
//       for (int j=1; j<=min(i,m); j++) {
//         for (int k=0; k<=800; k++) {
//           f[i][j][k] = f[i-1][j][k];
//           for (int l=1; l<=j; l++) {
//             path[i][j][k][l] = path[i-1][j][k][l];
//           }
//           if (k>=sub[i] && f[i-1][j-1][k-sub[i]]+sum[i]>f[i][j][k]) {
//             f[i][j][k] = f[i-1][j-1][k-sub[i]]+sum[i];
//             path[i][j][k][j] = i;
//             for (int l=j-1; l>=1; l--) {
//               path[i][j][k][l] = path[i-1][j-1][k-sub[i]][l];
//             }
//           }
//         }
//       }
//     }
//
//     for (int i=0; i<=20*m; i++) {
//       int s = f[n][m][i+fix] >= f[n][m][-i+fix] ? i : -i;
//       if (f[n][m][s+fix] < 0) {
//         continue;
//       }
//
//       for (int j=m; j>0; j--) {
//         jury[j] = path[n][m][s+fix][j];
//         psum += p[jury[j]];
//         dsum += d[jury[j]];
//       }
//       break;
//     }
//
//     printf("Jury #%d\n", ++cnt);
//     printf("Best jury has value %d for prosecution and value %d for defence:\n", psum, dsum);
//     for (int i=1; i<=m; i++)
//         printf(" %d", jury[i]);
//     printf("\n\n");
//   }
//
//   return 0;
// }
