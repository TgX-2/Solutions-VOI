#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 1007;
int n, m, a[maxn], b[maxn];
int dp[maxn][maxn];

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];

    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        if (a[i] == b[j]) dp[i][j] = dp[i - 2][j - 2] + 1;
        else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    cout << dp[n][m];

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}
