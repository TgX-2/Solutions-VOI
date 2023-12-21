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

const int maxn = 1e4+7;
int n, a[5][maxn], dp[maxn][11];
int mask[] = {0, 1, 2, 4, 5, 8, 9, 10};

int sol() {
    
	FOR(i,1,n) FOR(j,0,7) {
        int s = 0;
        FOR(id, 0, 3)
            if((mask[j] >> id) & 1) s += a[id][i];

        FOR(k,0,7) if(!(mask[k] & mask[j])) 
            maxi(dp[i][mask[j]], dp[i-1][mask[k]] + s);
        
	}

    int ans = intmin;
    FOR(i,0,7) maxi(ans, dp[n][mask[i]]);
    return ans;
}

void process() {
    int flag = intmin;
    cin >> n;
    FOR(i,0,3) FOR(j,1,n) {
        cin >> a[i][j];
        maxi(flag, a[i][j]);
    }

    if (flag < 0) return cout << flag, void();
    cout << sol();
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
3
-1 9 3
-4 5 -6
7 8 9
9 7 2

================================+
|OUTPUT                         |
--------------------------------|
32

===============================*/