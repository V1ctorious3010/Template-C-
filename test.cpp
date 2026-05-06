// g++ test.cpp -o test -mconsole
#include <bits/stdc++.h>
using namespace std;
#define getbit(x, i) ((x >> i) & 1)
#define fasty ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
const int N = 502;
int f[N][N];
int f2[N];
int a[N];
int n;
int calc(int l, int r){
    if(l == r - 1){
        if(a[l] == a[r])  return a[l] + 1;
        return 0;
    }
    if(l == r){
        return a[l];
    }
    if(f[l][r] != -1)  return f[l][r];
    int & tmp = f[l][r];
    tmp = 0;
    for(int k = l; k < r; k ++){
        if(calc(l, k) == calc(k + 1, r) && calc(l, k) != 0){
            tmp = calc(l, k) + 1;
        }
    }
    return tmp;
}
main(){
    fasty;
    //freopen("task.inp", "r", stdin);
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    memset(f, -1, sizeof f);
    memset(f2, 127, sizeof f2);
    f2[0] = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = i - 1; j >= 0; j --){
            if(calc(j + 1, i)){
                f2[i] = min(f2[i], f2[j] + 1);
            }
        }
    }
    /*for(int i = 1; i <= n; i ++){
        cout << f[i] << " ";
    } */
    cout << f2[n];
}
