#include<bits/stdc++.h>
///...................................*****.................................................///
///        Author :  Raihan Khan Raka  ( raihankhanraka@gmail.com )                         ///
///                  Department of Computer Science                                         ///
///                  & Engineering                                                          ///
///                  Comilla University , Bangladesh.                                       ///
///...................................*****.................................................///

/*....................................Values................................................*/
#define       inf                  1<<30
#define       p5                   100007
#define       p6                   1000007
#define       PI                   acos(-1)
#define       M                    1000000007

/*....................................Functions.............................................*/
#define       sqr(x)               x*x
#define       sc                   scanf
#define       pf                   printf
#define       scin(x)              sc("%d",&(x))
#define       scin2(x,y)            sc("d",&(x),&(y))
#define       scin3(x,y,z)          sc("d%d",&(x),&(y),&(z))
#define       scln(x)              sc("%lld",&(x))
#define       min3(a,b,c)          min(a,min(b,c))
#define       max3(a,b,c)          max(a,max(b,c))
#define       all(v)               v.begin(), v.end()
#define       ok                   cout << "ok" << endl
#define       mem(x,y)             memset(x,y,sizeof(x))
#define       READ(f)              freopen(f, "r", stdin)
#define       WRITE(f)             freopen(f, "w", stdout)

/*...................................Data_Types............................................*/
#define       lli                  long long int
#define       ull                  unsigned long long int
#define       pii                  pair < int, int>
#define       pll                  pair < ll, ll>
#define       veci                 vector<int>
#define       vecl                 vector<long long int>
#define       vecp                 vector<  pair<int,int> >
#define       mapstrint            map< string , int >
#define       mapstrstr            map< string , string >
#define       mapint               map< int, int >
#define       uset                 unordered_set
#define       umap                 unordered_map
#define       pq                   priority_queue

#define       pb                   push_back
#define       mp                   make_pair
#define       ss                   stringstream

/*.....................................Loops...............................................*/
#define       rep( i , a , b )     for( i=a ; i<b ; i++)
#define       rev( i , a , b )     for( i=a ; i>=b ; i--)
#define       repx( i ,a,b, x)     for( i=a ; i<b ; i+=x)

#define       FastRead             ios_base::sync_with_stdio(0);cin.tie(0)


//int month[]={31,28,31,30,31,30,31,31,30,31,30,31};
//long power(long int x, long int y){ int temp; if( y == 0) return 1; temp = power(x, y/2); if (y%2 == 0) return temp*temp; else return x*temp*temp; }
/*lli gcd(lli x,lli y)
{
    if(x==0) return y;
    return gcd(y%x,x);
}*/
/*
int dx[5] = {1, -1, 0, 0 };
int dy[5] = {0, 0, 1, -1};
*/

using namespace std;
int tree[4*p5];
int arr[p5];

void build(int v, int tl, int tr)
{
    if(tl==tr)
        tree[v]=arr[tl];
    else
    {
        int tm= (tl+tr)/2;
        build( 2*v, tl, tm);
        build( 2*v +1, tm+1, tr);

        tree[v]=min(tree[2*v] , tree[2*v+1] );
    }
}

int RMQ(int v, int tl, int tr, int l, int r)
{
    if( l > tr or r < tl ) return 0; // out of range

    if( l <= tl and r>=tr ) return tree[v]; // complete overlap

    int tm=(tl+tr)/2;

    int left_ans = RMQ(2*v, tl, tm, l, r);              // for partial overlap
    int right_ans = RMQ(2*v+1, tm+1, tr, l, r);

    return min(left_ans , right_ans) ;

}

void update_node(int v, int tl, int tr, int val, int pos)
{
    if(pos < tl or pos > tr) return;

    if(tl==tr and tl==pos)       // update the value
    {
        arr[pos]=val;  // original array update
        tree[v]=val;
        return;
    }

    int tm=(tl+tr)/2;

    if(pos <= tm)
        update_node(2*v, tl, tm, val, pos);
    else
        update_node(2*v+1, tm+1, tr, val, pos);

    tree[v]= min(tree[2*v] ,tree[2*v+1] );  // update whole segment tree
    return;
}

void update_range(int v,int tl, int tr, int l, int r,int inc)
{
    if(tr<tl or tl > r or tr < l ) return;

    if(tl==tr)     // update leaves
    {
        tree[v]+=inc;
        return;
    }

    int tm=(tl+tr)/2;
    update_range(2*v, tl, tm, l, r, inc);
    update_range(2*v+1, tm+1, tr, l, r, inc);

    tree[v]= min(tree[v*2] , tree[2*v+1]);
    return;
}
int main()
{
    int n,t,q,i,l,r;

    scin(t);

    while(t--)
    {
        scin(n);
        scin(q);

        rep(i, 0, n) scin(arr[i]);

        build( 1, 0, n-1);

        while(q--)
        {
            scin(l);
            scin(r);

            int sum = RMQ( 1, 0, n-1, l, r);    // Range sum query
            cout << sum << endl;
        }
        int inc=2;
        update_node(1, 0, n-1, 2, 5);
        update_range(1, 0, n-1, 1, 3, inc);

    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}


