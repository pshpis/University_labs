#include <bits/stdc++.h>

using namespace std;

int n;
vector<double> arr;
vector<vector<double> > merge_arrs;

int near_pow2(int x){
    int res = 1;
    while (res < x){
        res *= 2;
    }
    return res;
}

vector<double> my_merge(vector<double> a, vector<double> b){
    vector<double> res;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    while (a.size() > 0 && b.size() > 0){
        if (a.back() < b.back()){
            res.push_back(a.back());
            a.pop_back();
        }
        else {
            res.push_back(b.back());
            b.pop_back();
        }
    }

    while (a.size() > 0 || b.size() > 0){
        if (a.size() > 0){
            res.push_back(a.back());
            a.pop_back();
        }
        else if (b.size() > 0){
            res.push_back(b.back());
            b.pop_back();
        }
    }

    return res;
}

int main(){
    freopen("sortland.in", "r", stdin);
    freopen("sortland.out", "w", stdout);

    cin >> n;

    for (int i = 0; i < n; i ++){
        double x;
        cin >> x;
        arr.push_back(x);
    }

    int pow2_n = near_pow2(n);
    while (n < pow2_n){
        arr.push_back((double)-2e9);
        n ++;
    }

    for (int i = 0; i < n; i ++){
        merge_arrs.push_back(vector<double>(1, arr[i]));
    }

    vector<vector<double> > new_merge_arrs;

    while (merge_arrs.size() > 1){
//        cout << merge_arrs.size() << endl;
        for (int i = 0; i < merge_arrs.size(); i += 2){
            new_merge_arrs.push_back(my_merge(merge_arrs[i], merge_arrs[i + 1]));
        }

        merge_arrs = new_merge_arrs;
        new_merge_arrs.clear();
    }

    vector<double> res;

    for (int i = 0; i < merge_arrs[0].size(); i ++){
        if (merge_arrs[0][i] != -2e9) res.push_back(merge_arrs[0][i]);
    }

    double up = res.back(), down = res.front(), mid = res[res.size() / 2];

    int pos_up, pos_down, pos_mid;
    for (int i = 0; i < n; i ++){
        if (arr[i] == up) pos_up = i + 1;
        if (arr[i] == down) pos_down = i + 1;
        if (arr[i] == mid) pos_mid = i + 1;
    }

    cout << pos_down << " " << pos_mid << " " << pos_up << endl;
}
