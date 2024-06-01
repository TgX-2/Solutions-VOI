#include <bits/stdc++.h>
using namespace std;
main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, ans[3007]; cin >> n;
    string s; cin>>s; s = " " + s;
    for(int len=1;len<=(s.size()-1)/2;len++) {
        int cnt = 0, mmin = INT_MAX;
        for(int i=1;i<=(s.size()-1)-len+1;i++) {
            cnt += (s[i]!=s[i+len]);
            if(i>len) cnt-=(s[i-len]!=s[i]);
            if(i>=len) mmin=min(mmin,cnt);
        }
        ans[len]=mmin;
    }
    bool flag = 0;
    while(n--) {
        flag = 0;
        int k; cin>>k;
        for(int i=(s.size()-1)/2;i>=0;i--)
            if(ans[i]<=k) {cout << i << "\n"; flag = 1; break;}
        if (!flag) cout << 0 << "\n";
    }
}
