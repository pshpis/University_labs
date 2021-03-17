#include <bits/stdc++.h>

using namespace std;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(n, 0));

    for (int i = 0; i < m; i ++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;

        g[x][y]++;
//        g[y].push_back(x);
    }
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            cout << g[i][j] << " ";
        }
        cout <<"\n";
    }
}
