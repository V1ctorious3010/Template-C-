#include <bits/stdc++.h>
using namespace std;
#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x;})
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define forinc(x,a,b) for(int x=a;x<=b;x++)
#define fordec(x,a,b) for(int x=a;x>=b;x--)
#define forv(a,b) for(auto&a:b)
#define fi first
#define se second
#define pb push_back
#define ll long long
#define ii pair<int,int>
#define mt make_tuple
#define all(a) a.begin(),a.end()
#define reset(f,x) memset(f,x,sizeof(f))
#define getbit(x,i) ((x>>(i))&1)
#define batbit(x,i) (x|(1ll<<(i)))
#define tatbit(x,i) (x&~(1<<(i)))
#define gg exit(0);
#define debug(x) cerr << #x << " is " << x << "\n";
#define int long long
#define endl "\n"
int n;
int ans;
const int N=1e5+100;
int a[N],s[N];
struct point
{
    int x,y;
    int id;
    bool operator < (const point &A)
    {
       if(x!=A.x) return x<A.x;
       return y<A.y;
    }
};
struct cmp{
    bool operator () (const point& a, const point& b) const {
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    }
};

set<point,cmp>S;
vector<point>P;
int square_dist(point a,point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
main()
{
  fasty;
  //freopen("task.inp","r",stdin);
  cin>>n;
  forinc(i,1,n)
  {
      cin>>a[i];
      s[i]=s[i-1]+a[i];
      P.pb({i,s[i],i});
  }
  int inf=-1e10;
  sort(P.begin(),P.end());
  int sqD=square_dist(P[0],P[1]);
  for(auto [x,y,id]:P)
  {
     int d=sqrt(sqD)+1;
     point cur={inf,y-d,id};
     auto it=S.upper_bound(cur);
     while(it!=S.end())
     {
         if(it->y>y+d) break;
         if(it->x<x-d)
         {
             it=S.erase(it);
             continue;
         }
         if(square_dist(*it,{x,y,id})<sqD)
         {
             sqD=square_dist(*it,{x,y,id});
         }
         it++;
     }
     S.insert({x,y,id});
  }
  cout<<sqD<<endl;
}
