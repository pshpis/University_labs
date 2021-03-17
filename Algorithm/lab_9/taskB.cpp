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

vector<int> p;
int cycle_st = -1, cycle_fsh = -1;

bool color_dfs(int st){
    color[st] = 1;
    for (int u: g[st]){
        if (color[u] == 0){
            p[u] = st;
            if (color_dfs(u)) return true;
        }
        else if (color[u] == 1){
            cycle_fsh = st;
            cycle_st = u;
            return true;
        }
    }
    color[st] = 2;
    return false;
}

vector<int> get_cycle(){
    int n = g.size();
    color.assign(n, 0);
    used.assign(n, false);
    p.assign(n, -1);
    vector<int> res;
    for (int i = 0; i < n; i ++){
        if (color_dfs(i)) break;
    }

    if  (cycle_st == -1) return res;

    while (cycle_fsh != cycle_st){
        res.push_back(cycle_fsh);
        cycle_fsh = p[cycle_fsh];
    }

    res.push_back(cycle_st);
    reverse(res.begin(), res.end());

    return res;
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
//    freopen("topsort.in", "r", stdin);
//    freopen("topsort.out", "w", stdout);

    read_edges();
    vector<int> cycle = get_cycle();
    if (cycle.size() == 0){
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    for (int u: cycle) cout << u + 1 << " ";
}

