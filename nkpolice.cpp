#include <bits/stdc++.h>
#include <algorithm>
#include <queue>
using namespace std;
#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x;})
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r){return l+rng()%(r-l+1);}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define fori(x,a,b) for(int x=a;x<=b;x++)
#define ford(x,a,b) for(int x=a;x>=b;x--)
#define forv(a,b) for(auto&a:b)

#define fi first
#define se second
#define int long long
#define pb push_back

#define ll long long
#define ii pair<int,int>
#define mt make_tuple
#define all(a) a.begin(),a.end()

#define reset(f,x) memset(f,x,sizeof(f))
#define getbit(x,i) ((x>>(i))&1)
#define batbit(x,i) (x|(1ll<<(i)))
#define tatbit(x,i) (x&~(1<<(i)))
const int N=1e5+10;
int a[N];
vector<int> ke[N];
int n,m;
int khop[N],d[N];
int num[N],low[N],tail[N];
int P[N][25];
int it=0;
void dfs(int u,int p)
{
    low[u]=num[u]=++it;
    int child=0;
    fori(i,1,20)
    {
        P[u][i]=P[P[u][i-1]][i-1];
    }
    forv(v,ke[u]){
        if(v==p) continue;
        if( !num[v] ){
            ++child;
            d[v]=d[u]+1;
            P[v][0]=u;
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if( p==0 ){
                if( child>=2 ) khop[u]=1;
            }
            else if( low[v]>=num[u] ) khop[u]=1;
        }
        else{
            low[u]=min(low[u],num[v]);
        }
    }
    tail[u]=it;
}
int findPar(int u,int p){ // tim to tien cua u la con truc tiep cua p
    ford(i,20,0)
    {
        if(d[P[u][i]]>d[p])  u=P[u][i];
    }
    return u;
}
bool check(int u,int v){
    return num[v]<= num[u] && num[u]<=tail[v];
}
bool querry1(int a,int b,int g1,int g2)
{
    if( num[g1]>num[g2] ) swap(g1,g2);
    if( low[g2] !=num[g2] ) return true;
    if( check(a,g2) !=check(b,g2) ) return false;
    return true;
}
bool querry2(int a,int b,int c) // true=van di duoc
{
    if( !khop[c] ) return true;
    if( !check(a,c) && !check(b,c) ) return true;
    int pa=0,pb=0;
    if( check( a,c ) ) pa=findPar(a,c);
    if( check( b,c ) ) pb=findPar(b,c);
    if( pa==pb ) return true;
    if( !check(a,c) && low[pb] < num[c] ) return true;
    if( !check(b,c) && low[pa] < num[c] ) return true;
    if( check(a,c) && check(b,c) ) if( low[pa]<num[c] && low[pb] < num[c] ) return true;
    return false;
}

signed main()
{
    //freopen("task.inp","r",stdin);
    fasty;
    cin>>n>>m;
    fori(i,1,m){
        int u,v;
        cin>>u>>v;
        ke[u].pb(v);
        ke[v].pb(u);
    }
    d[1]=1;
    dfs(1,0);
    //cout<<"\n";
    //fori(i,1,n) cout << low[i]<<" "<<num[i]<<" "<<tail[i]<<"\n";
    int q;
    cin>>q;
    while(q--)
    {
        int t;
        cin>>t;
        if(t==1){
            int a,b,g1,g2;
            cin>>a>>b>>g1>>g2;
            cout<<(querry1(a,b,g1,g2)==1?"yes":"no")<<"\n"; //cat canh g1, g2
        }
        else{
            int a,b,c;
            cin>>a>>b>>c;
          //  cout<<querry2(a,b,c)<<"\n";
            cout<<(querry2(a,b,c)==1?"yes":"no")<<"\n";// cat dinh c
        }
    }
}
