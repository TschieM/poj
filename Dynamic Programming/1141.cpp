/*
Brackets Sequence
--------------------------------------------------------------------------------

Description:
Let us define a regular brackets sequence in the following way:
1. Empty sequence is a regular sequence.
2. If S is a regular sequence, then (S) and [S] are both regular sequences.
3. If A and B are regular sequences, then AB is a regular sequence.
For example, all of the following sequences of characters are regular brackets
sequences:
(), [], (()), ([]), ()[], ()[()]
And all of the following character sequences are not:
(, [, ), )(, ([)], ([(]
Some sequence of characters '(', ')', '[', and ']' is given. You are to find the
shortest possible regular brackets sequence, that contains the given character
sequence as a subsequence. Here, a string a1 a2 ... an is called a subsequence of
the string b1 b2 ... bm, if there exist such indices 1 = i1 < i2 < ... < in = m,
that aj = bij for all 1 = j = n.

Input:
The input file contains at most 100 brackets (characters '(', ')', '[' and ']')
that are situated on a single line without any other characters among them.

Output:
Write to the output file a single line that contains some regular brackets sequence
that has the minimal possible length and contains the given sequence as a subsequence.

Sample Input:
([(]

Sample Output:
()[()]
*/

#include<iostream>
#include<cstring>

using namespace std;
bool match(int i, int j);
void output(int i, int j);

char brackets[101];
int mark[101][101];

int main(){
  char c;
  int n = 0;
  while(cin.get(c) && c!='\n') brackets[++n] = c;

  int f[n+1][n+1];
  memset(mark,-1,sizeof(mark));
  memset(f,0,sizeof(f));
  for(int i=0;i<=n;i++) f[i][i] = 1;

  for(int j=1;j<n;j++){
    for(int i=1;i<=n-j;i++){
      f[i][i+j] = 9999;
      if(match(i,i+j) && f[i+1][i+j-1]<f[i][i+j]){
        f[i][i+j] = f[i+1][i+j-1];
        mark[i][i+j] = -1;
      }
      for(int k=i;k<i+j;k++){
        if(f[i][i+j]>f[i][k]+f[k+1][i+j]){
          f[i][i+j] = f[i][k]+f[k+1][i+j];
          mark[i][i+j] = k;
        }
      }
    }
  }

  output(1,n);
  cout<<endl;

  return 0;
}

bool match(int i, int j){
  if(brackets[i]=='(' && brackets[j]==')') return true;
  if(brackets[i]=='[' && brackets[j]==']') return true;
  return false;
}

void output(int i, int j){
  if(i>j) return ;
  if(i==j){
    if(brackets[i]=='('||brackets[i]==')') cout<<"()";
    if(brackets[i]=='['||brackets[i]==']') cout<<"[]";
    return ;
  }
  if(mark[i][j]==-1){
    cout<<brackets[i];
    output(i+1,j-1);
    cout<<brackets[j];
  }
  if(mark[i][j]!=-1){
    output(i,mark[i][j]);
    output(mark[i][j]+1,j);
  }
}
