#include <bits/stdc++.h>

using namespace std;

int main(){
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<vector<bool>> used(n, vector<bool>(m, false));

    pair<int, int> st = {0, 0}, fsh = {0, 0};
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < m; j ++){
            char c;
            cin >> c;

            if (c == '#') used[i][j] = true;
            if (c == 'S') st = {i, j};
            if (c == 'T') fsh = {i, j};
        }
    }

    vector<vector<int>> d(n, vector<int>(m, 0));

    queue<pair<int, int> > q;
    q.push(st);

    vector<pair<int, int> > move = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    vector<vector<pair<int, int>>> p(n, vector<pair<int, int>>(m, make_pair(0, 0)));

    while (!q.empty()){
        pair<int, int> v = q.front();
        q.pop();

        for (pair<int, int> mv: move){
            pair<int, int> u = v;
            u.first += mv.first;
            u.second += mv.second;

            if (u.first < 0 || u.first >= n || u.second < 0 || u.second >= m) continue;

            if (used[u.first][u.second]) continue;

            used[u.first][u.second] = true;
            q.push(u);
            d[u.first][u.second] = d[v.first][v.second] + 1;
            p[u.first][u.second] = v;
        }
    }

    if (d[fsh.first][fsh.second] == 0){
      cout << -1;
      return 0;
    }

    string res = "";

    while ((fsh.first != st.first) || (fsh.second != st.second)){
        pair<int, int> nw = p[fsh.first][fsh.second];
        pair<int, int> m = make_pair(nw.first - fsh.first, nw.second - fsh.second);
        fsh = nw;

        if (m.first == 0 && m.second == 1) res += "L";
        if (m.first == 1 && m.second == 0) res += "U";
        if (m.first == -1 && m.second == 0) res += "D";
        if (m.first == 0 && m.second == -1) res += "R";
    }

    reverse(res.begin(), res.end());
    cout << res.size() << endl;
    cout << res;

}
