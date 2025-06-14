#include<bits/stdc++.h>
using namespace std;

#define int long long

int t;
int n, m, p = INT_MAX, q = INT_MAX;
vector<array<int, 3>> pos;
int col[407][407];

int cal(const pair<int, int> &pos, const pair<int, int> &cheo1, const pair<int, int> &cheo2) {
    int a = 0;
    int b = 0;
    int x = pos.first, y = pos.second;

    for(int k = q; k <= m; k++) {
        if (col[x][k] == cheo1.first and col[y][k] == cheo1.second) a++;
        if (col[x][k] == cheo1.second and col[y][k] == cheo1.first) a++;
        if (col[x][k] == cheo2.first and col[y][k] == cheo2.second) b++;
        if (col[x][k] == cheo2.second and col[y][k] == cheo2.first) b++;
    }

    return a * b;
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    cin >> t;
    for(int i = 1; i <= t; i++) {
        int x, y, c; cin >> x >> y >> c;
        x += 200; y += 200;
        col[x][y] = c;
        n = max(n, x);
        m = max(m, y);
        p = min(p, x);
        q = min(q, y);
    }

    int ans = 0;
    for(int i = p; i <= n - 1; i++) for(int j = i + 1; j <= n; j++) {
        ans += cal({i, j}, {1, 2}, {3, 4});
        ans += cal({i, j}, {1, 3}, {2, 4});
        ans += cal({i, j}, {1, 4}, {2, 3});
    }

    cout << ans;

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}
