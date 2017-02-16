#include <bits/stdc++.h>
#define pi acos(-1)
#define sz(x) (int) x.size()
#define pii pair<int, int>
#define pill pair<int, long long>
#define mii map<int, int>
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define vb vector<bool>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define popb pop_back
#define all(v) v.begin(),v.end()
#define mod(x, m) ((x % m) + m) % m
#define mset(v, x) memset(v, x, sizeof(v))
#define mset2d(v, x, n) memset(v, x, sizeof(v[0][0]) * n * n)
#define mset2dd(v, x, n, m) memset(v, x, sizeof(v[0][0]) * n * m)
#define debug(x) cerr<<#x<<" : "<<x<<endl
#define debug2(x,y) cerr<<#x<<" : "<<x<<" & "<<#y<<" : "<<y<<endl
#define test() cerr<<"hola papa"<<endl
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;

const int N = 20;

/* Graph represented as and adjacency matrix */
bool ady[N][N];

/* Bitmask which represents all subsets in graph */
/* dp[i][j] Let i = subset, j = final node of a Hamiltonean path
/* dp[i][j] will denote the number of Hamiltonean paths from first bit with 1 of mask i to the node j*/
ll dp[1 << N][N];

/* n: number of nodes, m: number of edges, a & b: a pair of nodes connected by a path, ans: answer initialized in 0*/
ll n, m, a, b, ans = 0;

int main() {
  mset2dd(dp, 0, (1 << N), N);
  mset2d(ady, 0, N);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    /* Substract 1 because input nodes are numbered from 1 .. n and we need to start in 0 */
    ady[a - 1][b - 1] = ady[b - 1][a - 1] = 1;
  }
  /* We have to initialize every subsets where only one node is available (only one bit activated) */
  for (int i = 0; i < n; ++i) {
    dp[1 << i][i] = 1;
  }
  /* From 000...0001 to 111...1111...*/
  for (int mask = 1; mask < (1 << n); ++mask) {
    /* If subset (mask) is not power of 2, it means that contains more than 1 bit activated */
    if (mask & (mask - 1)) {
      /* We have to store the first bit of mask in order to check if there is a cycle */
      int first = -1;
      /* count: number of bits activated in mask, acum: number of Hamiltonean paths using all nodes from subset represented by mask */
      ll count = 0, acum = 0;
      for (int i = 0; i < n; ++i) {
        /* If bit i is activated */
        if (mask & (1 << i)) {
          /* Increase the number of bits activated in mask */
          ++count;
          /* To prevent check the first bit activated in mask with itself, because it is not a path */
          if (first != -1) {
            for (int j = 0; j < n; ++j) {
              /* If bit j is activated and also there is a path between i and j */
              if (mask & (1 << j) && ady[i][j]) {
                /* Number of Hamiltonean paths from first to i increases by number of hamiltonean paths from first bit of mask generated by turning off bit i, to j*/
                dp[mask][i] += dp[mask ^ (1 << i)][j];
              }
            }
          }
          /* Update first bit activated */
          if (first == -1) {
            first = i;
          }
          /* If there is a path from first node and i (final node), it means there is a cycle */
          if (ady[first][i]) {
              acum += dp[mask][i];
          }
        }
      }
      /* If the number of bits activated in mask are more than 2, I added to ans because its a valid cycle */
      if (count > 2) {
        ans += acum;
      }
    }
  }
  /* Print ans/2 to avoid repeated cycles like 1xyz2 and 2zyx1 */
  cout << ans / 2 << "\n";
}
