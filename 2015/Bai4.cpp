#include<bits/stdc++.h>
using namespace std;
#define int long long

// #include "debug.h"

const int maxn = 1007;
int n, m, q, a[maxn][maxn];

int get(int x1, int y1, int x2, int y2) {
    return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
}

int frow(int x, int x1, int y1, int x2, int y2) {
    return abs(get(x1, y1, x, y2) - get(x + 1, y1, x2, y2));
}

int fcol(int y, int x1, int y1, int x2, int y2) {
    return abs(get(x1, y1, x2, y) - get(x1, y + 1, x2, y2));
}

int row(int x1, int y1, int x2, int y2) {
    int l = x1, r = x2 - 1;
    for(int i = 1; i <= 25; i++) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        if (frow(mid1, x1, y1, x2, y2) <= frow(mid2, x1, y1, x2, y2)) r = mid2;
        else l = mid1;
    }
    int ans = (l + r) >> 1;
    return min({frow(ans, x1, y1, x2, y2),
                frow(l, x1, y1, x2, y2),
                frow(r, x1, y1, x2, y2)});
}

int col(int x1, int y1, int x2, int y2) {
    int l = y1, r = y2 - 1;
    for(int i = 1; i <= 25; i++) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        if (fcol(mid1, x1, y1, x2, y2) <= fcol(mid2, x1, y1, x2, y2)) r = mid2;
        else l = mid1;
    }
    int ans = (l + r) >> 1;
    return min({fcol(ans, x1, y1, x2, y2),
                fcol(l, x1, y1, x2, y2),
                fcol(r, x1, y1, x2, y2)});
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    }

    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= m; j++) {
            int x; cin >> x;
            a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + x;
        }

    while(q--) {
        int x1, y1; cin >> x1 >> y1;
        int x2, y2; cin >> x2 >> y2;

        cout << min(col(x1, y1, x2, y2), row(x1, y1, x2, y2)) << "\n";

    }


    return 0;
}
