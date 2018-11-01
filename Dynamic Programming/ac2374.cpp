#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>
#include <list>
using namespace std;
#define MP make_pair
#define x first
#define y second
const int INF = 0x3f3f3f3f;
const int maxn = 100010;
typedef pair<int, int> pii;
list<pii> p;
list<pii>::iterator it;
int w[maxn][2];
inline int f(int v)
{
    return v >= 0 ? v : -v;
}
int main()
{
    int n, s;
    int l, r;
    scanf("%d %d", &n, &s);
    for(int i = 0; i < n; i++) scanf("%d %d", &w[i][0], &w[i][1]);
    p.push_back(MP(0, s));
    for(int i = n - 1; i >= 0; i--){
        l = w[i][0], r = w[i][1];
        int ll = INF, rr = INF;
        for(it = p.begin(); it != p.end(); ){
            if(l <= it->y && it->y <= r){
                ll = min(ll, it->x + f(it->y - l));
                rr = min(rr, it->x + f(it->y - r));
                it = p.erase(it);
            }else if(it->y > r)
                break;
            else it++;
        }
        if(ll < INF){
            p.insert(it, MP(ll, l));
            p.insert(it, MP(rr, r));
        }
    }
    int ans = INF;
    for(it = p.begin(); it != p.end(); it++){
        ans = min(ans, it->x + f(it->y));
    }
    printf("%d\n", ans);
}
