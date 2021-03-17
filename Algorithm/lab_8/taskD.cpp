#include <bits/stdc++.h>

using namespace std;


void dfs(int st, vector<unordered_set<int>>& g, vector<bool>& used, vector<int>& comp, int comp_i){
    used[st] = true;
    comp[st] = comp_i;

    for (int u: g[st]){
        if (!used[u]){
            dfs(u, g, used, comp, comp_i);
        }
    }
}

vector<int> make_comp(vector<unordered_set<int> >& g){
    int n = g.size();
    vector<int> comp(n, 0);
    vector<bool> used(n, false);

    int cnt = 1;

    for (int i = 0; i < g.size(); i ++){
        if (!used[i]){
            dfs(i, g, used, comp, cnt);
            cnt ++;
        }
    }

    return comp;
}

int arr_max(vector<int>& arr){
    int mx = -1e9;
    for (int val: arr){
        mx = max(mx, val);
    }
    return mx;
}


int main(){
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<unordered_set<int>> g(n);

    for (int i = 0; i < m; i ++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;

        g[x].insert(y);
        g[y].insert(x);
    }

    vector<int> comp = make_comp(g);

    cout << arr_max(comp) << "\n";
    for (int comp_i: comp) cout << comp_i << " ";
    cout << endl;


}
