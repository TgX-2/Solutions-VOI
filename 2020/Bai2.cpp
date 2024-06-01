#include <bits/stdc++.h>
using namespace std;
const int MAX = (int) 1e5 + 5;
struct Edge{
    int u, v;
    int w;

    bool operator < (Edge &edge){
        return w < edge.w;
    }
};


int n, m, s, t;
int d[MAX];
vector <pair <int, int>> adj[MAX];
vector <Edge> edge;


void dijkstra(int i){
    priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pq;
    pq.push({d[i], i});
    while(pq.size()){
        pair <int, int> u = pq.top(); pq.pop();
        if(d[u.second] == u.first)
            for(pair <int, int> &v : adj[u.second])
                if(d[v.first] > max(u.first, v.second))
                    pq.push({d[v.first] = max(u.first, v.second), v.first});
    }
}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> m >> s >> t;
    for(int i = 1; i <= m; i++){
        int type, u, v, w; cin >> type >> u >> v >> w;
        if(type == 1){
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        else edge.push_back({u, v, w});
    }
    sort(edge.begin(), edge.end());
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    dijkstra(s);
    int res = d[t];
    for(Edge &e : edge){
        adj[e.u].push_back({e.v, 0});
        adj[e.v].push_back({e.u, 0});
        if(d[e.u] < d[e.v]) dijkstra(e.u);
        else if(d[e.v] < d[e.u]) dijkstra(e.v);
        res = min(res, d[t] + e.w);
    }
    cout << res;

    return 0;
}
