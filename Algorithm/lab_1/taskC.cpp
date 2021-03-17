#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> table;
vector<vector<int>> ans;

int turtle_rec(int i, int j){
    if (ans[i][j] != 0) return ans[i][j];
    ans[i][j] += table[i][j];
    if (i + 1 < n && j + 1 < m){
        ans[i][j] += max(turtle_rec(i + 1, j), turtle_rec(i, j + 1));
    }
    else if (j + 1 < m){
        ans[i][j] += turtle_rec(i, j + 1);
    }
    else if (i + 1 < n){
        ans[i][j] += turtle_rec(i + 1, j);
    }

    return ans[i][j];
}

int main(){
    freopen("turtle.in", "r", stdin);
    freopen("turtle.out", "w", stdout);

    cin >> n >> m;
    ans = vector<vector<int> >(n , vector<int> (m, 0));
    for (int i = 0; i < n; i ++){
        table.push_back(vector<int>(m));
        for (int j = 0; j < m; j ++){
            cin >> table[i][j];
        }
    }

    reverse(table.begin(), table.end());

    cout << turtle_rec(0, 0) << endl;



//    for (int i = 0; i < n; i ++){
//        for (int j = 0; j < m; j ++){
//            cout << table[i][j] << " ";
//        }
//        cout << "\n";
//    }
//
//    cout << endl;
//
//    for (int i = 0; i < n; i ++){
//        for (int j = 0; j < m; j ++){
//            cout << ans[i][j] << " ";
//        }
//        cout << "\n";
//    }

}
