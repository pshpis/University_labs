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

        if (g[y][x] == 1){
            cout << "YES";
        }
    }

    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            if (g[i][j] != g[j][i]){
                cout << "NO";
                return 0;
            }
            if (i == j && g[i][j] == 1){
                cout << "NO";
                return 0;
            }
        }
    }

    cout << "YES";
}
