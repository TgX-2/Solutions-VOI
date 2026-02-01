#include <bits/stdc++.h>

using namespace std;
const int limit = 2e3+4;

vector<int> a[limit];
int cnt, ltm, n, m;
int low[limit], num[limit], deleted[limit];
int in[limit], out[limit], dinh[limit], tplt[limit];
stack<int> s;

void dfs(int u){
    low[u] = num[u] = ++cnt;
    s.push(u);
    for(int v : a[u]){
        if(deleted[v]) continue;
        if(!num[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
    }
    if(low[u] == num[u]){
        ltm++;
        dinh[ltm] = u;
        int v;
        do{
            v = s.top();
            s.pop();
            tplt[v] = ltm;
            deleted[v] = true;
        }
        while(v != u);
    }
}

void ipt(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
    }
}

void proc(){
    for(int i = 1; i <= n; i++){
        if(!num[i]) dfs(i);
    }
    int d = 0;
    for(int u = 1; u <= n; u++){
        for(int v : a[u]){
            if(tplt[u]!=tplt[v]){
                d++;
                in[tplt[v]]++;
                out[tplt[u]]++;
            }
        }
    }
    if(d < 1){
        cout << "NO";
        exit(0);
    }
    cout << "YES" << '\n';
    for(int i = 1; i <= ltm; i++){
        if(out[i] == 0) cout << dinh[i] << " ";
    }
    for(int i = 1; i <= ltm; i++){
        if(in[i] == 0) cout << dinh[i] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ipt();
    proc();
    return 0;
}
