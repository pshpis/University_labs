#include <bits/stdc++.h>

using namespace std;

vector<unordered_set<int> > g;

void read_edges(){
    int n, m;
    cin >> n >> m;

    g.resize(n);

    for (int i = 0; i < m; i ++){
        int x, y;
        cin >> x >> y;
        x --; y --;

        g[x].insert(y);
    }
}

vector<bool> used;
vector<int> top_sort_res;
vector<int> color;

bool color_dfs(int st){
    color[st] = 1;
    for (int u: g[st]){
        if (color[u] == 0){
            if (color_dfs(u)) return true;
        }
        else if (color[u] == 1){
            return true;
        }
    }
    color[st] = 2;
    return false;
}

bool is_cycle(){
    int n = g.size();
    color.assign(n, 0);
    used.assign(n, false);
    for (int i = 0; i < n; i ++){
        if (!used[i]){
            if (color_dfs(i)) return true;
        }
    }
    return false;
}

void dfs(int st){
    used[st] = true;

    for (int u: g[st]){
        if (!used[u]) dfs(u);
    }

    top_sort_res.push_back(st);
}

void top_sort(){
    int n = g.size();
    used.clear();
    used.assign(n, false);
    top_sort_res.clear();

    for (int i = 0; i < n; i ++){
        if (!used[i]) dfs(i);
    }

    reverse(top_sort_res.begin(), top_sort_res.end());
}


int main(){
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);

    read_edges();
    top_sort();
    if (is_cycle()){
        cout << -1;
        return 0;
    }
    for (int u: top_sort_res) cout << u + 1 << " ";
}
