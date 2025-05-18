#include<bits/stdc++.h>
using namespace std;

#define int long long

#ifdef MaybeGonnaWin
#include "debug.h"
#else 
#define debug(...)
#endif 

const int maxn = 2007;
int n, d, a[maxn], pos[maxn];

int f(int x) {
    vector<int> dp;
    vector<pair<int, int>> v;

    for(int i = x; i <= n * 2; i++) {
        vector<int> tmp;
        for(int j = max(1LL, a[i] - d); j <= min(2 * n, a[i] + d); j++) 
            if (pos[j] < x) 
                tmp.emplace_back(pos[j]);
        if (!tmp.empty()) {
            sort(tmp.begin(), tmp.end(), greater<int>());
            for(const int &val : tmp) {
                auto it = lower_bound(dp.begin(), dp.end(), val);
                if (it == dp.end()) dp.emplace_back(val);
                else *it = val;
            }
        }
    }

    return (int)(dp.size());
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.ans", "w", stdout);
    }

    cin >> n >> d;
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    int ans = 0;

    for(int i = 1; i <= n * 2; i++)
        ans = max(ans, f(i));

    cout << ans;

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}
