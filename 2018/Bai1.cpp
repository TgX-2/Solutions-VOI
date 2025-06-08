#include<bits/stdc++.h>
using namespace std;

const int dx[5] = {-1, 0, 1, 0};
const int dy[5] = {0, -1, 0, 1};

const int maxn = 1007;
int n, x, y, s;
char a[maxn][maxn];

int vis[maxn][maxn][4];
pair<int, int> ans;

bool flag = 0;
void dfs(int x, int y, int dir) {
    if (flag) return;

    int xx = x + dx[dir];
    int yy = y + dy[dir];

    if (xx < 1 or xx > n or yy < 1 or yy > n) {
        ans = {x + dx[dir] * s, y + dy[dir] * s};
        flag = 1;
        return;
    }

    if (a[xx][yy] == '#') {
        dfs(x, y, (dir + 1) % 4);
        return;
    }

    if (vis[xx][yy][dir] != 0) 
        s %= (vis[xx][yy][dir] - s);
    else vis[xx][yy][dir] = s;

    if (s <= 0) return ans = {x ,y}, void();

    --s;
    dfs(xx, yy, dir);
}

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> x >> y >> s; swap(x, y);

    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        cin >> a[i][j];

    if (x < 1 or y < 1 or y > n or (x - s) > n) {
        x -= s;
        swap(x, y);
        return cout << x << " " << y, 0;
    }

    if (x > n) {
        s -= x - (n + 1);
        x = n + 1;
    }

    vis[x][y][0] = s;
    dfs(x, y, 0);

    swap(ans.first, ans.second);
    cout << ans.first << " " << ans.second;

    cerr << "Time : " << clock() * 1.0 / CLOCKS_PER_SEC << " ms." << endl;
    return 0;
}
