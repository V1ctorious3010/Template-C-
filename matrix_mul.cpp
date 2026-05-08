#include <bits/stdc++.h>
using namespace std;
#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x;})
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r) {return l+rng()%(r-l+1);}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define fori(x,a,b) for(int x=a;x<=b;x++)
#define ford(x,a,b) for(int x=a;x>=b;x--)
#define fi first
#define se second
#define forv(a,b) for(auto&a:b)
#define pb push_back
#define all(a) a.begin(),a.end()
#define ii pair<int,int>
#define reset(f,x) memset(f,x,sizeof(f))
#define getbit(x,i) ((x>>i)&1)
#define batbit(x,i) (x|(1ll<<i))
#define tatbit(x,i) (x&~(1<<i))
#define gg exit(0);

#define int long long

const int mod = 1e9 + 7;
int n,m;
struct matrix
{
    int M[102][102];
    matrix() {reset(M,0);}
};
matrix operator*(matrix a,matrix b)
{
    matrix res;
    fori(i,1,m) fori(j,1,m)
    {
        fori(k,1,m)
        {
            res.M[i][j]+=1ll*a.M[i][k]*b.M[k][j]%mod;
            if(res.M[i][j]>=mod) res.M[i][j]-=mod;
        }
    }
    return res;
}

matrix pw(matrix a,int b)
{
    matrix res;
    fori(i,1,m) fori(j,1,m) res.M[i][j] = (i==j);
    while(b)
    {
        if(b&1) res=res*a;
        a=a*a;
        b/=2;
    }
    return res;
}
main()
{
    fasty;
    //freopen("task.inp","r",stdin);
    cin>>n>>m;
    if(n<m) cout<<1,gg;

    matrix tg;
    tg.M[1][1] = 1,tg.M[1][m] = 1;
    fori(i,2,m) fori(j,1,m) tg.M[i][j] = (i-1==j);
    matrix res = pw(tg,n-m+1);

    int kq = 0;
    fori(i,1,m)
    {
        kq+=res.M[1][i];
        if(kq>=mod) kq-=mod;
    }
    cout<<kq;
}

