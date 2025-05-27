#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 1e6 + 6;
int n;
pair<int, int> a[maxn];

bool check(int t) {
    vector<int> l(n, 0);
    vector<int> r(n, 0);

    for(int i = 1; i <= n; i++) {
        l[i - 1] = max(1LL, a[i].first - t / a[i].second);
        r[i - 1] = min(n, a[i].first + t / a[i].second);
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    for(int i = 0; i <= n - 1; i++) 
        if (l[i] > i + 1 or i + 1 > r[i]) return 0;
    return 1;
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y;
        a[i] = {x, y};
    }

    int l = 0, r = INT_MAX, ans = r;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }

    cout << ans;

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}
