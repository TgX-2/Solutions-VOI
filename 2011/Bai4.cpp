#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 2e5 + 7;
int n;
pair<int, int> a[maxn];

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first < b.first;
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
        int x; cin >> x;
        a[i] = {x, 0};
    }

    for(int i = n + 1; i <= n + n; i++) {
        int x; cin >> x;
        a[i] = {x, 1};
    }

    sort(a + 1, a + 1 + n + n, cmp);

    int ans = 0;
    for(int i = 2; i <= n + n; i++) {
        if ((a[i].second == 0 and a[i - 1].second == 1) or 
            (a[i].second == 1 and a[i - 1].second == 0)) {
            ans++;
            a[i].second = 2;
            a[i - 1].second = 2;
        }
    }

    cout << ans;
    return 0;
}
