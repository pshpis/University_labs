#include <bits/stdc++.h>

using namespace std;

class Graph{
public:
    vector<unordered_set<int>> g, rev_g;
    vector<int> component;
    vector<int> order;
    vector<bool> used;

    Graph() = default;

    Graph(int n){
        g.resize(n);
        rev_g.resize(n);
        component.assign(n, -1);
        used.assign(n, false);
    }

    void read_edges(){
        int n, m; cin >> n >> m;
        g.resize(n);
        rev_g.resize(n);
        for (int i = 0; i < m; i ++){
            int x, y;
            cin >> x >> y;
            x --; y --;

            add_edge(x, y);
        }
        component.assign(n, -1);
        used.assign(n, false);
    }

    void dfs1(int st){
        used[st] = true;
        for (int u: g[st]){
            if (!used[u]) dfs1(u);
        }
        order.push_back(st);
    }

    void dfs2(int st, int comp_id){
        used[st] = true;
        component[st] = comp_id;
        for (int u: rev_g[st]){
            if (!used[u]) dfs2(u, comp_id);
        }
    }

    void solve(){
        int n = g.size();
        int comp_id = 0;

        make_top_sort();

        used.assign(n, false);

        for (int u: order){
            if (!used[u]){
                dfs2(u, comp_id);
                comp_id ++;
            }
        }

//        cout << "Dfs1 and dfs2 ended" << endl;
//        cout << comp_id << endl;
//        for (int i = 0; i < n; i ++) cout << component[i] << " ";
//        cout << endl;
        Graph comp_g(comp_id);

        for (int u = 0; u < n; u ++){
            for (int v: g[u]){
                if (component[u] != component[v]) comp_g.add_edge(component[u], component[v]);
            }
        }

//        cout << "Comp_g created" << endl;

        comp_g.make_top_sort();
        vector<int> real_comp(comp_id);
        for (int i = 0; i < comp_id; i ++){
            int comp = comp_g.order[i];
            real_comp[comp] = i;
        }



        cout << comp_id << endl;
        for (int i = 0; i < g.size(); i ++){
            cout << real_comp[component[i]] + 1 << " ";
        }

    }

    void add_edge(int x, int y){
        g[x].insert(y);
        rev_g[y].insert(x);
    }


    void make_top_sort(){
        int n = g.size();
        order.clear();
        used.assign(n, false);
        for (int i = 0; i < n; i ++){
            if (!used[i]) dfs1(i);
        }
        reverse(order.begin(), order.end());
    }


};

int main(){
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);
    Graph g;
    g.read_edges();
    g.solve();
}
