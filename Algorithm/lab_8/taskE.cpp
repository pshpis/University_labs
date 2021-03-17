#include <bits/stdc++.h>

using namespace std;

int main(){
    freopen("pathbge1.in", "r", stdin);
    freopen("pathbge1.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector<unordered_set<int>> g(n);

    for (int i = 0; i < m; i ++){
        int x, y;
        cin >> x >> y;
        x --; y --;

        g[x].insert(y);
        g[y].insert(x);
    }


    int st = 0;
    queue<int> q;
    vector<int> d(n, 0);
    vector<bool> used(n, false);

    q.push(st);
    used[st] = true;

    while (!q.empty()){
        int v = q.front();
        q.pop();

        for (int u: g[v]){
            if (!used[u]){
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
            }
        }
    }

    for (int i = 0; i < n; i ++) cout << d[i] << " ";
    cout << endl;

    return 0;
}
