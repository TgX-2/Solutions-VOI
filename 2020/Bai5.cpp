#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 1e5 + 7;
int n; 
array<int, 4> rec[maxn], comprec[maxn];

vector<int> valVer, valHor;
vector<array<int, 3>> compHor[maxn << 1], compVer[maxn << 1];
vector<int> g[maxn];
void compress() {
    sort(valVer.begin(), valVer.end());
    valVer.erase(unique(valVer.begin(), valVer.end()), valVer.end());
    sort(valHor.begin(), valHor.end());
    valHor.erase(unique(valHor.begin(), valHor.end()), valHor.end());

    for(int i = 1; i <= n; i++) {
        comprec[i][0] = lower_bound(valVer.begin(), valVer.end(), rec[i][0]) - valVer.begin();
        comprec[i][1] = lower_bound(valHor.begin(), valHor.end(), rec[i][1]) - valHor.begin();
        comprec[i][2] = lower_bound(valVer.begin(), valVer.end(), rec[i][2]) - valVer.begin();
        comprec[i][3] = lower_bound(valHor.begin(), valHor.end(), rec[i][3]) - valHor.begin();
    }

    for(int i = 1; i <= n; i++) {
        int x = comprec[i][0], y = comprec[i][1], p = comprec[i][2], q = comprec[i][3];
        compVer[x].push_back({y, 0, i});
        compVer[x].push_back({q, 1, i});
        compVer[p].push_back({y, 0, i});
        compVer[p].push_back({q, 1, i});

        compHor[y].push_back({x, 0, i});
        compHor[y].push_back({p, 1, i});
        compHor[q].push_back({x, 0, i});
        compHor[q].push_back({p, 1, i});
    }

    vector<pair<int, int>> edge;

    for(int i = 1; i <= (int)(valVer.size()) - 1; i++) {
        unordered_set<int> s;
        sort(compVer[i].begin(), compVer[i].end(), [](const array<int, 3> &a, const array<int, 3> &b) {
            if (a[0] == b[0]) return a[2] < b[2];
            return a[0] < b[0];
        });

        for(const array<int, 3> &val : compVer[i]) {
            int too = val[0], typ = val[1], idx = val[2];
            if (typ == 1) s.erase(idx);
            else {
                for(const int &pos : s)
                    edge.push_back({min(pos, idx), max(pos, idx)});
                s.insert(idx);
            }
        }
    }

    for(int i = 1; i <= (int)(valHor.size()) - 1; i++) {
        unordered_set<int> s;
        sort(compHor[i].begin(), compHor[i].end(), [](const array<int, 3> &a, const array<int, 3> &b) {
            if (a[0] == b[0]) return a[2] < b[2];
            return a[0] < b[0];
        });

        for(const array<int, 3> &val : compHor[i]) {
            int too = val[0], typ = val[1], idx = val[2];
            if (typ == 1) s.erase(idx);
            else {
                for(const int &pos : s) 
                    edge.push_back({min(pos, idx), max(pos, idx)});
                s.insert(idx);
            }
        }
    }

    sort(edge.begin(), edge.end());
    edge.erase(unique(edge.begin(), edge.end()), edge.end());

    for(const pair<int, int> &val : edge) {
        int x = val.first, y = val.second;
        g[x].push_back(y);
        g[y].push_back(x);
    }

}

int num[maxn], low[maxn], cnt = 0;
int child[maxn];
vector<int> bri;
void dfs(int u, int pre) {
    child[u] = 1;
    num[u] = low[u] = ++cnt;

    for(const int &v : g[u]) if (v != pre) {
        if (num[v]) low[u] = min(low[u], num[v]);
        else {
            dfs(v, u);
            child[u] += child[v];

            low[u] = min(low[u], low[v]);
            if (low[v] >= num[v])
                bri.push_back(v);
        }
    }
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
        int x, y, p, q; cin >> x >> y >> p >> q; swap(y, q);
        rec[i] = {x, y, p, q};
        valVer.emplace_back(x);
        valHor.emplace_back(y);
        valVer.emplace_back(p);
        valHor.emplace_back(q);
    }

    compress();

    int ans = INT_MAX;
    for(int i = 1; i <= n; i++) if (num[i] == 0) {
        bri.clear();
        dfs(i, i);

        for(const int &val : bri)
            ans = min(ans, abs(child[val] - child[i] + child[val]));
    }
    
    if (ans == INT_MAX) cout << -1;
    else cout << ans;

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}