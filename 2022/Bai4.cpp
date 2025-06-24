#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 2e5 + 7;
int n;
array<int, 3> a[maxn];

bool cmp(const array<int, 3> &a, const array<int, 3> &b) {
    if (a[1] == b[1]) return a[0] < b[0];
    return a[1] < b[1];
}

int seg[maxn << 2], lazy[maxn << 2];

void down(int id) {
    int x = lazy[id];
    seg[id << 1] += x;
    seg[id << 1 | 1] += x;
    lazy[id << 1] += x;
    lazy[id << 1 | 1] += x;
    lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if (v < l or r < u) return;
    if (u <= l and r <= v) {
        seg[id] += val;
        lazy[id] += val;
        return;
    }
    down(id);
    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v, val);
    update(id << 1 | 1, mid + 1, r, u, v, val);
    seg[id] = max(seg[id << 1], seg[id << 1 | 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (v < l or r < u) return INT_MIN;
    if (u <= l and r <= v) return seg[id];
    down(id);
    int mid = (l + r) >> 1;
    return max(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("temp.inp", "r")) {
        freopen("temp.inp", "r", stdin);
        freopen("temp.out", "w", stdout);
    } else {
        freopen("SSEQ.inp", "r", stdin);
        freopen("SSEQ.out", "w", stdout); 
    }

    vector<int> val;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int l, r, w; cin >> l >> r >> w;
        val.push_back(l);
        val.push_back(r);
        a[i] = {l, r, w};
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int m = (int)(val.size());

    sort(a + 1, a + 1 + n, cmp);
    for(int i = 1; i <= n; i++) {
        a[i][0] = lower_bound(val.begin(), val.end(), a[i][0]) - val.begin() + 1;
        a[i][1] = lower_bound(val.begin(), val.end(), a[i][1]) - val.begin() + 1;
    }


    int ans = 0;
    for(int i = 1; i <= n; i++) {
        update(1, 1, m, 1, a[i][0], a[i][2]);
        ans = max(ans, get(1, 1, m, 1, a[i][1]));
    }

    cout << ans;

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms.\n";
    return 0;
}
