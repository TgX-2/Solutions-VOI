/*------------DEFINE-----------*/
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a), _b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i>=_b; --i)
#define FORSq(i,a,b) for(int i=(a), _b=(b); i*i<=_b; ++i)
#define FORC(i,a,b,c) for(int i=(a), _b=(b), _c=(c); i<=_b; i+=_c)
#define FORSt(i,s) for(int i=0, _s=(int)(s.size());i<_s;++i)

#define fi first
#define se second
#define pb push_back
#define len(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
#define alln(x,n) (x)+1, (x)+1+(n)
#define _ <<" "<<
#define __ << "\n"
#define ___ << " "
#define file "voi"
#define int long long
#define _______________mgw______________ main()

#define intmax INT_MAX
#define intmin INT_MIN 
#define llongmax LLONG_MAX 
#define llongmin LLONG_MIN

using    namespace std;
typedef  long long ll;
typedef  string st;
typedef  pair<int,int> pii;
typedef  vector<int> vi;
typedef  vector<pii> vpii;

void fastio(st name, st inp, st out, st dbg) {
    if (fopen((name + "." + inp).c_str(), "r")) {
        freopen((name + "." + inp).c_str(), "r", stdin);
        freopen((name + "." + out).c_str(), "w", stdout);
        freopen((name + "." + dbg).c_str(), "w", stderr);
    }        
}

template<typename T1, typename T2> bool mini(T1 &a, T2 b)
    {if(a>b) a=b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b)
    {if(a<b) a=b; else return 0; return 1;}

/*------------CODE-------------*/

const int maxn = 507;

struct edge {
    int v, t, c;
    edge() : v(0), t(0), c(0) {}
    edge(int v, int t, int c) : v(v), t(t), c(c) {}

    bool operator < (const edge& other) const {
        return t > other.t;
    }
} a[maxn];

int n,m;
int cc[maxn][maxn], tt[maxn][maxn];
vector<int> g[maxn], d(maxn, intmax);
bool charge[maxn];

void inp() {
    cin >> n;
    FOR(i,1,n) cin >> charge[i];
    cin >> m;
    FOR(i,1,m) {
        int u,v,t,c; cin >> u >> v >> t >> c;
        g[u].pb(v); g[v].pb(u);
        cc[u][v] = cc[v][u] = c;
        tt[u][v] = tt[v][u] = t;
    }
}

void dijk() {
    d[n] = 0;
    priority_queue<pii, vpii, greater<pii>> q;
    q.push({n,0});

    while (!q.empty()) {
        auto x = q.top(); q.pop();
        int u = x.fi, t = x.se;

        for(auto v:g[u]) {
            if (d[v] > d[u] + tt[v][u]) {
                d[v] = d[u] + tt[v][u];
                q.push({v, d[v]});
            }
        }
    }
}

bool check(int power) {
    queue<edge> q;
    q.push(edge(1,0,power));

    while (!q.empty()) {
        auto x = q.front(); q.pop();
        int u = x.v, t = x.t, c = x.c;

        for(auto v:g[u]) {
            if (c < cc[u][v] || t + tt[u][v] + d[v] > d[1]) continue;
            int wv = (charge[v] ? power : c - cc[u][v]);
            int tv = t + tt[u][v];
            if (v == n && tv == d[1]) return 1;
            q.push(edge(v, tv, wv));
        }
    }
    return 0;
}

void sol() {
    int l = 1, r = intmax, ans = 0;
    while(l<=r) {
        int mid = (l+r)>>1;
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans;
}

void process() {
    inp();
    dijk();
    sol();
}



/*------------MAIN-------------*/
_______________mgw______________ {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);  
    fastio(file, "inp", "out", "debug");
    process();
}


/*==============================+
|INPUT                          |
--------------------------------|
4
0 1 1 0
5
1 2 5 4
1 3 4 3
1 4 9 4
2 4 4 1
3 4 5 2

================================+
|OUTPUT                         |
--------------------------------|
3

===============================*/
