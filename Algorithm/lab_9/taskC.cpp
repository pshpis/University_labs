#include <bits/stdc++.h>

using namespace std;

vector<unordered_set<int> > g;

bool is_shit = false;

void read_edges(){
    int n, m;
    cin >> n >> m;

    g.resize(n);

    for (int i = 0; i < m; i ++){
        int x, y;
        cin >> x >> y;
        x --; y --;

        if (x == y){
            is_shit = true;
            continue;
        }

        g[x].insert(y);
        g[y].insert(x);
    }
}

vector<int> part;

bool bfs_bipartite(int st){
    int n = g.size();
    queue<int> q;
    q.push(st);
    part[st] = 0;

    while (!q.empty()){
        int v = q.front();
        q.pop();

        for (int u: g[v]){
            if (part[u] == -1){
                part[u] = 1 - part[v];
                q.push(u);
            }
            if (part[u] == part[v]){
                return false;
            }
        }
    }

    return true;
}

bool check_bipartite(){
    part.assign(g.size(), -1);
    for (int i = 0; i < g.size(); i ++){
        if (part[i] == -1 && !bfs_bipartite(i)) return false;
    }
    return true;
}


int main(){
//    freopen("topsort.in", "r", stdin);
//    freopen("topsort.out", "w", stdout);

    read_edges();
    if (is_shit){
        cout << "NO";
        return 0;
    }
    if (check_bipartite()) cout << "YES";
    else cout << "NO";

}

