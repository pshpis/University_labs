#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("smallsort.in", "r", stdin);
    freopen("smallsort.out","w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, j, n;

    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    for (int i = 1; i < n; i ++){
            j = i - 1;
            t = a[i];
            while (j > -1 && a[j] > t) {
                a[j + 1] = a[j];
                j = j - 1;
            }
            a[j + 1] = t;
    }


    for (int i = 0; i < n; i ++){
        cout << a[i] << ' ';
    }

}
