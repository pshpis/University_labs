#include <bits/stdc++.h>

using namespace std;

void counting_sort(vector<string> &a, int k){
    int n = a.size();
    vector<vector<string> > c(260);
    for (int i = 0; i < n; i ++){
        c[(int)a[i][k]].push_back(a[i]);
    }


    int pos = 0;
    for (int i = 0; i < 260; i ++){
        for (int j = 0; j < c[i].size(); j ++){
            a[pos] = c[i][j];
            pos ++;
        }
    }
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    vector<string> a(n);
    for (int i = 0; i < n; i ++) cin >> a[i];

    for (int i = m - 1; i > m - k - 1; i --){
        counting_sort(a, i);
    }

    for (int i = 0; i < a.size(); i ++){
        cout << a[i] << "\n";
    }
}
/*
*/
