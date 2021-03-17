#include <bits/stdc++.h>

using namespace std;

#define int int64_t

int lowerBound(vector<int>& a, int x){
    int n = a.size();

    if (n == 0){
        return -1;
    }
    if (n == 1){
        if (a[0] == x) return 0;
        return -1;
    }
    if (a.front() > x || a.back() < x) return -1;

    int left = -1, right = n;

    while (right - left > 1){
        int mid = (right + left) / 2;

        if (a[mid] < x) left = mid;
        else right = mid;
    }

    if (a[right] == x) return right + 1;

    return -1;

}

int upperBound(vector<int>& a, int x){
    int n = a.size();

    if (n == 0){
        return -1;
    }
    if (n == 1){
        if (a[0] == x) return 0;
        return -1;
    }
    if (a.front() > x || a.back() < x) return -1;

    int left = -1, right = n;

    while (right - left > 1){
        int mid = (right + left) / 2;

        if (a[mid] <= x) left = mid;
        else right = mid;
    }

     if (a[right - 1] == x) return right;

    return -1;
}

int32_t main(){
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i ++) cin >> a[i];

    int m; cin >> m;
    for (int i = 0; i < m; i ++){
        int x; cin >> x;
        int ans1 = lowerBound(a, x);
        int ans2 = upperBound(a, x);
        cout << ans1 << " " << ans2 << "\n";
    }
}
