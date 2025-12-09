#include <bits/stdc++.h>
using namespace std;

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef complex<double> cpx;
template <typename T> using minPq = priority_queue<T, vector<T>, greater<T>>;
#define ms(a, x) memset(a, x, sizeof(a))
#define pb push_back
#define fs first
#define sn second
#define ALL(v) begin(v), end(v)
#define SZ(v) ((int) (v).size())
#define lbv(v, x) (lower_bound(ALL(v), x) - (v).begin())
#define ubv(v, x) (upper_bound(ALL(v), x) - (v).begin())
template <typename T> inline void UNIQUE(vector<T> &v){sort(ALL(v)); v.resize(unique(ALL(v)) - v.begin());}
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1);
#define FR(i, n) for(int i = 0; i < (n); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define FORR(i, a, b) for(int i = (a); i >= (b); i--)
#define dbg(x) {cerr << #x << ' ' << x << endl;}
#define dbgArr(arr, n) {cerr << #arr; FR(_i, n) cerr << ' ' << (arr)[_i]; cerr << endl;}
template <typename T, typename U>
ostream& operator<<(ostream &os, pair<T, U> p){return os << "(" << p.fs << ", " << p.sn << ")";}

mt19937 rng(430298584);
int randInt(int a, int b){return uniform_int_distribution(a, b)(rng);}

// Number of nodes
const int MIN_N = 15;
const int MAX_N = 30;

// Number of connected components
const int MIN_COMP = 2;
const int MAX_COMP = 6;

// Number of queries
const int MIN_Q = 20;
const int MAX_Q = 30;

// Number of edges after spanning tree
const int MIN_E = 0;
const int MAX_E = 20;

// Number of unique possible IDs. Also need to adjust %02d manually
const int MAX_ID = MAX_N;

int n, numComps;
vpii edges;
vector<pair<pii, bool>> out;
int idMap[MAX_N];
bitset<MAX_ID> usedId;

vi adjList[MAX_N];
int qu[MAX_N], ql, qr;
bool vis[MAX_N];

void bfs(int src){
    ql = qr = 0;
    qu[qr++] = src;
    vis[src] = true;
    printf("start %02d src %02d\n", idMap[src], idMap[src]);

    while(ql < qr){
        int n1 = qu[ql++];
        for(int n2 : adjList[n1]) if(!vis[n2]){
            vis[n2] = true;
            qu[qr++] = n2;
            printf("%02d %02d src %02d\n", idMap[n1], idMap[n2], idMap[src]);
        }
    }
}

int main(int argc, char **argv){
    int tc = atoi(argv[1]);
    rng.seed(tc*4892 + 1290);
    // Generate main graph parameters
    n = randInt(MIN_N, MAX_N);
    numComps = randInt(MIN_COMP, MAX_COMP);

    // Each component gets at least 2 nodes
    // For each remaining node, randomly put it in a component
    vector<vi> comps(numComps);
    FR(i, numComps*2) comps[i/2].pb(i);
    FOR(i, numComps*2, n) comps[randInt(0, numComps-1)].pb(i);

    // Connect each component with a spanning tree
    FR(c, numComps){
        FOR(i, 1, SZ(comps[c])){
            int par = comps[c][randInt(0, i-1)];
            edges.pb({par, comps[c][i]});
        }
    }

    // Add more random edges within components
    int remEdges = randInt(MIN_E, MAX_E);
    while(remEdges--){
        int c = randInt(0, numComps-1);
        int a = comps[c][randInt(0, SZ(comps[c])-1)];
        int b = comps[c][randInt(0, SZ(comps[c])-1)];
        edges.pb({a, b});
    }

    // Randomly label and shuffle output
    FR(i, n){
        int id;
        do id = randInt(0, MAX_ID-1); while(usedId[id]);
        idMap[i] = id;
        usedId[id] = true;
    }

    printf("Graph\n");
    shuffle(ALL(edges), rng);
    for(auto &[a, b] : edges){
        if(rng() & 1) swap(a, b);
        printf("%02d %02d\n", idMap[a], idMap[b]);
    }

    printf("Queries\n");
    int q = randInt(MIN_Q, MAX_Q);
    while(q--){
        int a, b;

        // 50% of answers should be yes, 50% should be no
        if(rng() & 1){
            int c = randInt(0, numComps-1);
            a = comps[c][randInt(0, SZ(comps[c])-1)];
            b = comps[c][randInt(0, SZ(comps[c])-1)];
            out.pb({{a, b}, true});
        }
        else {
            int c1 = randInt(0, numComps-1);
            int c2 = randInt(0, numComps-2);
            if(c2 >= c1) c2++;
            a = comps[c1][randInt(0, SZ(comps[c1])-1)];
            b = comps[c2][randInt(0, SZ(comps[c2])-1)];
            out.pb({{a, b}, false});
        }
        printf("%02d %02d\n", idMap[a], idMap[b]);
    }

    // BFS in the most natural order given the input
    vi ord;
    usedId.reset();

    printf("Thinking\n");
    for(auto [a, b] : edges){
        adjList[a].pb(b);
        adjList[b].pb(a);
        if(!usedId[a]) usedId[a] = true, ord.pb(a);
        if(!usedId[b]) usedId[b] = true, ord.pb(b);
    }
    for(int n1 : ord) if(!vis[n1]) bfs(n1);

    printf("Output\n");
    for(auto [p, res] : out){
        auto [a, b] = p;
        printf("%02d %02d %s\n", idMap[a], idMap[b], res ? "yes" : "no");
    }
    printf("End\n");
}
