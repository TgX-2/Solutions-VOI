/*-----------------------------
        Author : TgX.2
       11Ti - K28 - CHV
-----------------------------*/

#include <bits/stdc++.h>

#define FOR(i, a, b)       for (int i = (a), _b = (b); i <= _b; i += 1)
#define FORD(i, a, b)      for (int i = (a), _b = (b); i >= _b; i -= 1)
#define FORC(i, a, b, c)   for (int i = (a), _b = (b), _c = (c); i <= _b; i += _c)

#define fi                 first
#define se                 second
#define pb                 push_back
#define len(x)             (int)((x).size())
#define all(x)             (x).begin(), (x).end()

#define _                  << " " <<
#define __                 << "\n"

#define ______________TgX______________ main()
#define int                long long
#define intmax             1e9
#define intmin            -1e9
#define llongmax           1e18
#define llongmin          -1e18
#define memo(a, val)       memset((a), (val), sizeof((a)))

using   namespace std;
typedef long long          ll;
typedef pair<int, int>     pii;

template<typename T1, typename T2> 
bool mini(T1 &a, T2 b)
    {if (a > b) a = b; else return 0; return 1;}

template<typename T1, typename T2> 
bool maxi(T1 &a, T2 b)
    {if (a < b) a = b; else return 0; return 1;}
/*-----------------------------*/

const int maxn = 2007;
int n, d, a[maxn], pos[maxn];
int tar;

unordered_map<int, bool> is;

auto cmp = [](const int &a, const int &b) {
    return a > b;
};
set<int, decltype(cmp)> chose(cmp);

int doo() {
    vector<int> dp;
    FOR(i, 1, tar) {
        chose.clear();
        FOR(j, max(1LL, a[i] - d), min(2 * n, a[i] + d)) {
            if (is[j] == 1)
                chose.insert(pos[j]);
        }
        for(int val : chose) {
            auto it = lower_bound(all(dp), val);
            if (it == dp.end())
                dp.pb(val);
            else *it = val;
        }
    }
    return len(dp);
}

void process() {
    cin >> n >> d;
    FOR(i, 1, 2 * n) {
        cin >> a[i];
        pos[a[i]] = i;
        is[a[i]] = 1;
    }

    int ans = 0;
    FOR(i, 1, 2 * n) {
        is[a[i]] = 0;
        tar = i;
        maxi(ans, doo());
    }

    cout << ans;
}



/*-----------------------------*/
______________TgX______________ {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);  
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }
    process();
}


/*==============================+
|INPUT                          |
--------------------------------|

================================+
|OUTPUT                         |
--------------------------------|

===============================*/
