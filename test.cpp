 // g++ test.cpp -o test -mconsole
#include <bits/stdc++.h>
using namespace std;
#define getbit(x, i) ((x >> i) & 1)
#define fasty ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
const int N = 1e6 + 10;
int pi[N];
int f[N];
int b[N];

void kmp(string &s){
    pi[1] = 0;
    for(int i = 2; i <= s.size() - 1; i ++){
        int k = pi[i - 1];
        while(k && s[k + 1] != s[i])   k = pi[k];
        if(s[k + 1] == s[i])  k ++;
        pi[i] = k;
    }
}
signed main(){
    fasty;
    //freopen("task.inp","r",stdin);
    int T;
    cin >> T;
    while(T --){
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        while(q --){
            int l, r;
            cin >> l >> r;
            string tmp = s.substr(l - 1, r - l + 1);
            tmp = " " + tmp;
            kmp(tmp);
            int res = 0;
            for(int i = 1; i <= r - l + 1; i ++){
                if(pi[i] == 0)   b[i] = i;
                else b[i] = b[pi[i]];
                f[i] = f[i - b[i]] + 1;
                res += f[i];
            }
            cout << res << endl;
        }

    }
}
