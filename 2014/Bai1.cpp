#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 3e5 + 7;
int n, aa, bb, a[maxn], b[maxn];
pair<int, int> pos[maxn];

int bs(int u) {
    int l = u, r = n;
    int ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        int ca = a[mid] - a[u - 1];
        int cb = b[mid] - b[u - 1];
        if (ca >= aa and cb >= bb) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    return ans;
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    cin >> n >> aa >> bb;
    for(int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        pos[i] = {a, b};
    }

    sort(pos + 1, pos + 1 + n);

    for(int i = 1; i <= n; i++) {
        a[i] = a[i - 1];
        b[i] = b[i - 1];
        if (pos[i].second == 1) a[i]++;
        else b[i]++;
    }

    int ans = INT_MAX;
    for(int i = 1; i <= n - 1; i++) {
        int j = bs(i);
        if (j != -1) 
            ans = min(ans, pos[j].first - pos[i].first);
    }

    if (ans == INT_MAX) cout << "-1";
    else cout << ans;
    
    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}