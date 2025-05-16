#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 307;
int n, k, a[maxn];

int f[maxn][maxn][maxn];
int dp(int l, int r, int cnt) {
    if (cnt == 0) return 0;
    if (l > r) return LLONG_MIN;

    int &ans = f[l][r][cnt];
    if (ans != -1) return ans;

    ans = 0;
    ans = max(ans, dp(l + 1, r, cnt));
    ans = max(ans, dp(l, r - 1, cnt));
    if (l + 1 <= r) ans = max(ans, dp(l + 2, r, cnt - 1) + abs(a[l] - a[l + 1]));
    if (r - 1 >= l) ans = max(ans, dp(l, r - 2, cnt - 1) + abs(a[r] - a[r - 1]));
    if (l + 1 <= r) ans = max(ans, dp(l + 1, r - 1, cnt - 1) + abs(a[l] - a[r]));
    return ans;

}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];

    memset(f, -1, sizeof(f));
    cout << dp(1, n, k);

    return 0;
}
