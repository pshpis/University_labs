#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int> > a;

void siftDown(int i) {
    int n = a.size();

    int start_i = i;
    int left_i = 2 * i + 1;
    int right_i = 2 * i + 2;

    if (left_i < n && a[left_i].first < a[i].first) i = left_i;
    if (right_i < n && a[right_i].first < a[i].first) i = right_i;

    if (start_i != i) {
        swap(a[i], a[start_i]);
        siftDown(i);
    }
}

void siftUp(int i) {
    if (i != 0){
        if (a[i].first < a[(i - 1) / 2].first){
            swap(a[i], a[(i - 1) / 2]);
            siftUp((i - 1) / 2);
        }
    }
}

int find_by_key(int key){
    for (int i = 0; i < a.size(); i++)
        if (a[i].second == key) return i;
}

void push(int new_val, int key){
    a.push_back({new_val, key});
    siftUp(a.size() - 1);
}

int extract_min(){
    int result = a[0].first;
    swap(a[0], a[a.size() - 1]);
    a.pop_back();
    siftDown(0);

    return result;
}

void change_el_by_key(int key, int new_val){
    int j = find_by_key(key);
    a[j].first = new_val;

    if (j != 0 && a[j].first < a[(j - 1) / 2].first) siftUp(j);
    else siftDown(j);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    freopen("priorityqueue.in", "r", stdin);
    freopen("priorityqueue.out", "w", stdout);

    string s;
    int i = 0;

    while (cin >> s) {
        i++;

        if (s.size() == 0) break;

        if (s == "push") {
            int new_val; cin >> new_val;
            push(new_val, i);
        }

        if (s == "extract-min") {
            if (a.size() == 0){
                cout << "*\n";
                continue;
            }

            cout << extract_min() << "\n";
        }

        if (s == "decrease-key") {
            int key, new_val;
            cin >> key >> new_val;

            change_el_by_key(key, new_val);

        }
    }

}

