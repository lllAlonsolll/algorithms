// Depth First Search O(V + E)
#include "../macros.h"

const int N = 100;
vi ady[N];
vector<bool> vis(N);

// Recursive Approach
void dfs(int u) {
    vis[u] = true;
    
    for (auto v: ady[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

// Iterative approach
void dfs(int u) {
    stack<int> st;
    st.push(u);

    while (!st.empty()) {
        int x = st.top(); st.pop();
        vis[x] = true;

        for (auto v: ady[u]) {
            if (!vis[v]) {
                st.push(v);
            }
        }
    }
}

// Used to classify edges
vi color(N, 0); // 0: Not visited, 1: Visiting, 2: Visited and exited
vi d(N, 0); // Discovery time
vi f(N, 0); // Finishing time
vi p(N, -1); // Parents
int t = 0;

void dfs(int u) {
    d[u] = t++;
    color[u] = 1;
    for (int v: ady[u]) {
        if (color[v] == 0) {
            p[v] = u;
            dfs(v);
        }
    }
    color[u] = 2;
    f[u] = t++;
}