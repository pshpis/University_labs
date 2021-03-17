#include <bits/stdc++.h>

using namespace std;


class Graph{
public:
    int edges_count;
    int nodes_count;
    unordered_set<int> erased_nodes;
    vector<unordered_set<int> > gr;

    Graph(int sz){
        nodes_count = sz;
        edges_count = 0;
        gr = vector<unordered_set<int> >(nodes_count);
    }

    void add_edge(int x, int y){
        if (gr[x].count(y) == 0 || gr[x].count(y) == 0){
            edges_count ++;
        }

        gr[x].insert(y);
        gr[y].insert(x);
    }

    vector<int> get_isolated_nodes(){
        vector<int> res;
        for (int i = 0; i < nodes_count; i ++){
            if (gr[i].size() == 0 && erased_nodes.count(i) == 0) res.push_back(i);
        }
        return res;
    }

    void erase_node(int x){
        for (int u: gr[x]){
            gr[u].erase(x);
            edges_count --;
        }
        gr[x].clear();
        erased_nodes.insert(x);
    }

    vector<pair<int, int> > sorted_nodes(){
        vector<pair<int, int> > res;
        for (int i = 0; i < nodes_count; i ++){
            res.push_back({gr[i].size(), i});
        }

        sort(res.begin(), res.end());
        return res;
    }

    void dfs1 (int v, vector<bool>& used, vector<int>& order){
        used[v] = true;
        for (auto u: gr[v])
            if (!used[u])
                dfs1(u, used, order);
        order.push_back(v);
    }

    void dfs2 (int v, vector<bool>& used, unordered_set<int>& component){
        used[v] = true;
        component.insert(v);
        for (auto u: gr[v])
            if (!used[u])
                dfs2(u, used, component);
    }

    int dfs(int v, vector<bool>& used){
        used[v] = true;
        int mx = 0;
        for (auto u: gr[v]){
            if (!used[u]){
                int t = dfs(u, used);
                if (t > mx){
                    mx = t;
                }
            }
        }
        return mx + 1;
    }

    vector<unordered_set<int> > get_components(){
        vector<bool> used;
        vector<int> order;
        unordered_set<int> component;
        vector<unordered_set<int> > res;

        used.assign(nodes_count, false);
        for (int i = 0; i < nodes_count; ++ i)
            if (!used[i])
                dfs1(i, used, order);

        used.assign(nodes_count, false);
        for (int i = 0; i < nodes_count; ++ i){
            int v = order[nodes_count-1-i];
            if (!used[v]) {
                dfs2(v, used, component);
                res.push_back(component);
                component.clear();
            }
        }

        return res;
    }

    int get_component_distance(unordered_set<int>& component){
        int dist = 0;
        vector<bool> used(nodes_count, false);
        for (int u: component){
            dist = max(dist, dfs(u, used));
            used.assign(nodes_count, false);
        }
        return dist;
    }

    int get_max_component_distance(){
        vector<unordered_set<int> > components = get_components();
        int res = 0;
        int max_component_size = -1;
        for (auto c: components){
            if ((int)c.size() > max_component_size){
                max_component_size = c.size();
                res = get_component_distance(c);
            }
        }
        return res;
    }

    vector<int> get_distance(int s, int to){
        int n = nodes_count;
        queue<int> q;
        q.push(s);
        vector<bool> used(nodes_count, false);
        vector<int> d(n, 0), p(n, -1);
        used[s] = true;
        p[s] = -1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u: gr[v]){
                if (!used[u]) {
                    used[u] = true;
                    q.push(u);
                    d[u] = d[u] + 1;
                    p[u] = v;
                }
            }
        }

        vector<int> path;
        if (used[to]){
            for (int v = to; v != -1; v = p[v])
                path.push_back(v);
            reverse(path.begin(), path.end());
        }

        return path;
    }
};


int main(){
    freopen("edges.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph g(1000);
    int x;
    while (cin >> x){
        int y;
        cin >> y;
        g.add_edge(x, y);
    }

    cout << "Edges count - " << g.edges_count << endl;

    cout << "Isolated nodes  - " << endl;
    vector<int> res = g.get_isolated_nodes();
    cout << res.size() << endl;
    for (int t: res) cout << t << " ";
    cout << endl;


    cout << "Max nodes degrees" << endl;
    vector<pair<int, int> > sorted_nodes = g.sorted_nodes();
    cout << sorted_nodes.back().first << endl;
    int i = g.nodes_count - 1;
    while (sorted_nodes[i].first == sorted_nodes.back().first){
        cout << sorted_nodes[i].second << " ";
        i --;
    }
    cout << endl;


    cout << "Max component distance" << endl;
    cout << g.get_max_component_distance() << endl;

    int A = 50, B = 611, C = 764, D = 804, E = 647, F = 968;

    cout << "Distance between A and B" << endl;
    res = g.get_distance(A, B);
    cout << res.size() - 1 << endl;
    for (int t: res) cout << t << " ";
    cout << endl;

    cout << "Distance between C and D" << endl;
    res = g.get_distance(C, D);
    cout << res.size() - 1 << endl;
    for (int t: res) cout << t << " ";
    cout << endl;

    cout << "Distance between E and F" << endl;
    res = g.get_distance(E, F);
    cout << res.size() - 1 << endl;
    for (int t: res) cout << t << " ";
    cout << endl;

    vector<int> need_erase = {552, 139, 973, 77, 594, 274, 789, 949};
    x = 0;
    while (x < 1000){
        need_erase.push_back(x);
        x += 17;
    }
    for (int t: need_erase){
        g.erase_node(t);
    }

    cout << "\nAfter Deleting\n" << endl;

    cout << "Edges count - " << g.edges_count << endl;

    cout << "Isolated nodes  - " << endl;
    res = g.get_isolated_nodes();
    cout << res.size() << endl;
    for (int t: res) cout << t << " ";
    cout << endl;


    cout << "Max nodes degrees" << endl;
    sorted_nodes = g.sorted_nodes();
    cout << sorted_nodes.back().first << endl;
    i = g.nodes_count - 1;
    while (sorted_nodes[i].first == sorted_nodes.back().first){
        cout << sorted_nodes[i].second << " ";
        i --;
    }
    cout << endl;

    cout << "Max component distance" << endl;
    cout << g.get_max_component_distance() << endl;

    cout << "Distance between A and B" << endl;
    res = g.get_distance(A, B);
    cout << res.size() - 1 << endl;
    for (int t: res) cout << t << " ";
    cout << endl;

    cout << "Distance between C and D" << endl;
    res = g.get_distance(C, D);
    cout << res.size() - 1 << endl;
    for (int t: res) cout << t << " ";
    cout << endl;

    cout << "Distance between E and F" << endl;
    res = g.get_distance(E, F);
    cout << res.size() - 1 << endl;
    for (int t: res) cout << t << " ";
    cout << endl;


}
