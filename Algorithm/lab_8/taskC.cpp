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

        if (g[x][y] == 0 && g[y][x] == 0){
            g[x][y] = 1;
        }
        else {
                cout << "YES";
                return 0;
        }
    }

    cout << "NO";
    return 0;
}
