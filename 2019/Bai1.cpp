#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 2007;
int n, m, x, y;
int a[maxn][maxn], b[maxn][maxn];

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    cin >> m >> n;
    for(int i = 1; i <= m; i++) 
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
            a[i][j + n] = a[i + m][j] = a[i + m][j + n] = a[i][j];
        }

    for(int i = 1; i <= 2 * m; i++)
        for(int j = 1; j <= 2 * n; j++)
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];

    int t; cin >> t;
    while(t--) {
        int typ; cin >> typ;
        if (typ == 0) {
            int r, d; cin >> r >> d;
            x += r; x %= n;
            y += d; y %= m;
        } else {
            int u, v, s, t; cin >> u >> v >> s >> t;
            u = (u + y) % (2 * m);
            v = (v + x) % (2 * n);
            s = (s + y) % (2 * m);
            t = (t + x) % (2 * n);

            cout << (b[s][t] - b[u - 1][t] - b[s][v - 1] + b[u - 1][v - 1]) << "\n";
        }
    }

    return 0;
}
