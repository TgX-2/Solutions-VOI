#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define vii vector<int>
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define endl '\n'
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

using namespace std;
const int mod = 1e9+7;
const ll inf = 2e18+7;
const int lmt = 1e3+4;

ll f[lmt][lmt][2];
int q, m, n, c[lmt][lmt];

void in(){
	cin >> m >> n;
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++) cin >> c[i][j];
    }
    memset(f, 0x7f, sizeof(f));

    for(int i = 1; i <= m; i++) f[i][0][0] = 0; 
	for(int j = 1; j <= n; j++) f[0][j][1] = 0;
}

void proc(){
	
	cin >> q;
	while(q--){
    	in();
    	for(int i = 1; i <= m; i++){
        	for(int j = 1; j <= n; j++){
            	f[i][j][0] = min(f[i-1][j][0], f[i-1][j][1] + c[i][j]);
            	f[i][j][1] = min(f[i][j-1][1], f[i][j-1][0] + c[i][j]);
        	}
        }
    	cout << min(f[m][n][0], f[m][n][1]) << endl;
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("tt.inp","r",stdin);
    //freopen("tt.out","w",stdout);
    
    proc();

    cerr << "Time elapsed: " << TIME << "s" << endl; 
    return 0;
}
