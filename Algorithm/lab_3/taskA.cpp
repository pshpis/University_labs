#include <bits/stdc++.h>

using namespace std;

#define int int64_t

vector<pair<int, int> > a;

void heapify(int smal_i){
    int start_i = smal_i;
    int left_i = 2 * smal_i + 1;
    int right_i = 2 * smal_i + 2;
    int n = a.size();

    if (left_i < n && a[left_i].first < a[smal_i].first) smal_i = left_i;
    if (right_i < n && a[right_i].first < a[smal_i].first) smal_i = right_i;

    if (smal_i != start_i){
        swap(a[start_i], a[smal_i]);
        heapify(smal_i);
    }
}


void goUp(int i) {
    if (i != 0){
        if (a[i].first < a[(i - 1) / 2].first){
            swap(a[i], a[(i - 1) / 2]);
            goUp((i - 1) / 2);
        }
    }
}

void push(int el, int key){
    a.push_back({el, key});
    goUp(a.size() - 1);
}


int extract_min(){
    if (a.size() == 0) return (int)2e9;
    int res = a[0].first;
    swap(a[0], a[a.size() - 1]);
    a.pop_back();
    heapify(0);

    return res;
}

int32_t main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    freopen("priorityqueue.in", "r", stdin);
    freopen("priorityqueue.out", "w", stdout);

    string s;
    int i = 0;

    while (cin >> s){
        if (s == "push"){
            int new_el; cin >> new_el;
            push(new_el, i);
        }
        if (s == "extract-min"){
            int res = extract_min();
            if (res == (int)2e9){
                cout << "*\n";
            }
            else {
                cout << res << "\n";
            }
        }
        if (s == "decrease-key"){
            int key, new_val; // place is second index
            cin >> key >> new_val;
            key --;
            int need_i = -1;

            for (int i = 0; i < a.size(); i ++){
                if (a[i].second == key){
                    need_i = i;
                    break;
                }
            }

            if (need_i != 0 && a[need_i].first < a[(need_i - 1) / 2].first)
                goUp(need_i);
            else
                heapify(need_i);
        }
        i ++;
    }

}
