#include <bits/stdc++.h>

using namespace std;

//QUICK SORT START

template<typename T>
bool is_sort(vector<T>& a, int start_id, int end_id){
    for (int i = start_id; i < end_id - 1; i ++){
        if (a[i] > a[i + 1]) return false;
    }
    return true;
}

// help function for qsort
template<typename T>
void quick_sort(vector<T>& a, int start_id, int end_id){

    if (end_id <= start_id + 1) return;

    int start_el_id = start_id;
    for (int i = start_id + 1; i < end_id; i ++){
        if (a[i] < a[start_el_id]){
            swap(a[i], a[start_el_id + 1]);
            swap(a[start_el_id + 1], a[start_el_id]);
            start_el_id ++;
        }
    }

    if (start_el_id + 1 - start_id > 1) quick_sort(a, start_id, start_el_id + 1);
    if (end_id - start_el_id - 1 > 1) quick_sort(a, start_el_id + 1, end_id);
}

template<typename T>
void qsort(vector<T>& a){
    if (is_sort(a, 0, a.size())) return;
    quick_sort(a, 0, a.size());
}

// QUICK SORT END

// MERGE SORT START
int near_pow2(int x){
    int res = 1;
    while (res < x){
        res *= 2;
    }
    return res;
}

long long inverse_count = 0;

template<typename T>
vector<T> my_merge(vector<T> a, vector<T> b){
    vector<T> res;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    while (a.size() > 0 && b.size() > 0){
        if (a.back() <= b.back()){
            res.push_back(a.back());
            a.pop_back();
        }
        else {
            if (a.back() > b.back()){
                inverse_count += a.size();
//                cout << b.back() << " " << a.size() << endl;
            }
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

template<typename T>
T get_max_el(vector<T>& a){
//    if (a.size() == 0) return;

    T res = a[0];
    for (int i = 1; i < a.size(); i ++){
        if (a[i] > res) res = a[i];
    }

    return res;
}

template<typename T>
void mergesort(vector<T>& a){
    if (a.size() < 2) return;

    int n = a.size();
    int start_size = n;
    int pow_2 = near_pow2(n);
    T max_el = get_max_el(a);

    while (n < pow_2){
        n ++;
        a.push_back(max_el);
    }

    vector<vector<T> > merge_arrs, new_merge_arrs;

    for (int i = 0; i < n; i ++){
        merge_arrs.push_back(vector<T>(1, a[i]));
    }

    while (merge_arrs.size() > 1){
        for (int i = 0; i < merge_arrs.size(); i += 2){
            new_merge_arrs.push_back(my_merge(merge_arrs[i], merge_arrs[i + 1]));
        }

        merge_arrs = new_merge_arrs;
        new_merge_arrs.clear();
    }

    a = merge_arrs[0];
    while (a.size() != start_size) a.pop_back();
}

// Merge Sort End

void antiqs(vector<int>& a){
    for (int i = 0; i < a.size(); i ++){
        swap(a[i], a[i/2]);
    }
}
int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

//    freopen("antiqs.in", "r", stdin);
//    freopen("antiqs.out", "w", stdout);

    int n;
    cin >> n;

    vector<int> a;

    for (int i = 0; i < n; i ++) a.push_back(i);
    antiqs(a);

    for(int i = 0; i < n; i ++) cout << a[i] + 1 << " ";

}


