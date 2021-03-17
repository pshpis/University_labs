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

    if (end_id <= start_id) return;

    int start_el = a[(start_id + end_id) / 2];
    int left_id = start_id, right_id = end_id;

    while (left_id <= right_id){
        while (a[left_id] < start_el) left_id ++;
        while (a[right_id] > start_el) right_id --;

        if (left_id >= right_id) break;
        swap(a[left_id ++], a[right_id --]);
    }

    int start_el_id = right_id;

    quick_sort(a, start_id, start_el_id);
    quick_sort(a, start_el_id + 1, end_id);
}

template<typename T>
void qsort(vector<T>& a){
    if (is_sort(a, 0, a.size())) return;
    reverse(a.begin(), a.end());
    if (is_sort(a, 0, a.size())) return;
    reverse(a.begin(), a.end());
    quick_sort(a, 0, a.size() - 1);
}

// QUICK SORT END


template<typename T>
void separation(vector<T>& a, int start_id, int end_id, int need_el_id){
    int start_el = a[(start_id + end_id) / 2];
    int left_id = start_id, right_id = end_id;

    while (left_id < right_id){
        while (a[left_id] < start_el){
            left_id ++;
        }
        while (a[right_id] > start_el){
            right_id --;
        }
        if (left_id <= right_id){
            swap(a[left_id], a[right_id]);
            left_id ++;
            right_id --;
        }

    }

    if (start_id < right_id && need_el_id <= right_id) separation(a, start_id, right_id, need_el_id);
    if (end_id > left_id && need_el_id >= left_id) separation(a, left_id, end_id, need_el_id);
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

//    freopen("kth.in", "r", stdin);
//    freopen("kth.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    int A, B, C, a1, a2;
    cin >> A >> B >> C >> a1 >> a2;


    vector<int> a(n);
    a[0] = a1;
    a[1] = a2;

    for (int i = 2; i < n; i ++){
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }
//
//    for (int i = 0; i < n; i ++){
//        cout << a[i] << " ";
//    }
//    cout << endl;

    separation(a, 0, n - 1, k - 1);

    cout << a[k - 1];

//    for (int i = 0; i < n; i ++){
//        cout << a[i] << " ";
//    }
//    cout << endl;
//
//    qsort(a);
//    for (int i = 0; i < n; i ++){
//        cout << a[i] << " ";
//    }
}

