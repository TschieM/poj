/*
Description

In a shop each kind of product has a price. For example, the price of a flower is
2 ICU (Informatics Currency Units) and the price of a vase is 5 ICU. In order to
attract more customers, the shop introduces some special offers.
A special offer consists of one or more product items for a reduced price. Examples:
three flowers for 5 ICU instead of 6, or two vases together with one flower for
10 ICU instead of 12.

Write a program that calculates the price a customer has to pay for certain items,
making optimal use of the special offers. That is, the price should be as low as
possible. You are not allowed to add items, even if that would lower the price.
For the prices and offers given above, the (lowest) price for three flowers and
two vases is 14 ICU: two vases and one flower for the reduced price of 10 ICU and
two flowers for the regular price of 4 ICU.
Input

Your program is to read from standard input. The first line contains the number b
of different kinds of products in the basket (0 <= b <= 5). Each of the next b lines
contains three values c, k, and p. The value c is the (unique) product code (1 <= c <= 999).
The value k indicates how many items of this product are in the basket (1 <= k <= 5).
The value p is the regular price per item (1 <= p <= 999). Notice that all together
at most 5*5=25 items can be in the basket. The b+2nd line contains the number s of
special offers (0 <= s <= 99). Each of the next s lines describes one offer by giving
its structure and its reduced price. The first number n on such a line is the number
of different kinds of products that are part of the offer (1 <= n <= 5). The next
n pairs of numbers (c,k) indicate that k items (1 <= k <= 5) with product code c
(1 <= c <= 999) are involved in the offer. The last number p on the line stands for
the reduced price (1 <= p <= 9999). The reduced price of an offer is less than the
sum of the regular prices.
Output

Your program is to write to standard output. Output one line with the lowest possible
price to be paid.

Sample Input

2
7 3 2
8 2 5
2
1 7 3 5
2 7 1 8 2 10

Sample Output

14
*/

#include <iostream>

using namespace std;

#define INF 0x7ffffff

struct offer{
  int n, c[10], k[1005], p;
};

int b, s;
int c[10], k[10], p[10];
offer offers[105];
int dp[10][10][10][10][10];

int main() {
  cin >> b;
  for (int i=1; i<=b; i++) {
    cin >> c[i] >> k[i] >> p[i];
  }
  for (int i=b+1; i<=5; i++) {
    c[i] = k[i] = p[i] = 0;
  }
  cin >> s;
  for (int i=1; i<=s; i++) {
    for (int j=1; j<=1005; j++) {
      offers[i].k[j] = INF;
    }
    for (int j=1; j<=5; j++) {
      offers[i].k[c[j]] = 0;
    }
    cin >> offers[i].n;
    for (int j=1; j<=offers[i].n; j++) {
      cin >> offers[i].c[j];
      cin >> offers[i].k[offers[i].c[j]];
    }
    cin >> offers[i].p;
  }

  dp[0][0][0][0][0] = 0;
  for (int i1=0; i1<=k[1]; i1++) {
    for (int i2=0; i2<=k[2]; i2++) {
      for (int i3=0; i3<=k[3]; i3++) {
        for (int i4=0; i4<=k[4]; i4++) {
          for (int i5=0; i5<=k[5]; i5++) {
            dp[i1][i2][i3][i4][i5] = i1*p[1] + i2*p[2] + i3*p[3] + i4*p[4] + i5*p[5];
            for (int j=1; j<=s; j++) {
              int r1 = i1 - offers[j].k[c[1]];
              int r2 = i2 - offers[j].k[c[2]];
              int r3 = i3 - offers[j].k[c[3]];
              int r4 = i4 - offers[j].k[c[4]];
              int r5 = i5 - offers[j].k[c[5]];
              if (r1<0 || r2<0 || r3<0 || r4<0 || r5<0) {
                continue;
              }
              dp[i1][i2][i3][i4][i5] = min(dp[i1][i2][i3][i4][i5], dp[r1][r2][r3][r4][r5]+offers[j].p);
            }
          }
        }
      }
    }
  }

  cout << dp[k[1]][k[2]][k[3]][k[4]][k[5]] << endl;

  return 0;
}
