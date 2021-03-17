#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> arr;
vector<vector<int> > merge_arrs;

int near_pow2(int x){
    int res = 1;
    while (res < x){
        res *= 2;
    }
    return res;
}

vector<int> my_merge(vector<int> a, vector<int> b){
    vector<int> res;

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
//    freopen("sort.in", "r", stdin);
//    freopen("sort.out", "w", stdout);

    cin >> n;

    for (int i = 0; i < n; i ++){
        int x;
        cin >> x;
        arr.push_back(x);
    }

    for (int i = 0; i < n; i ++){
        merge_arrs.push_back(vector<int>(1, arr[i]));
    }

    vector<vector<int> > new_merge_arrs;

    while (merge_arrs.size() > 1){
//        cout << merge_arrs.size() << endl;
        for (int i = 0; i < merge_arrs.size(); i += 2){
            new_merge_arrs.push_back(my_merge(merge_arrs[i], merge_arrs[i + 1]));
        }

        merge_arrs = new_merge_arrs;
        new_merge_arrs.clear();
    }

    vector<int> res = merge_arrs[0];

    for (int i = 0; i < res.size(); i ++){
        if (res[i] != -2e9) cout << res[i] << " ";
    }

    cout << endl;
}
