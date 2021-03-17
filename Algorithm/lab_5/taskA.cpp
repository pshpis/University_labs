#include <bits/stdc++.h>

using namespace std;

#define int int64_t

class Node{
public:
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    int value;

    Node(int value_, Node* left_, Node* right_, Node* parent_){
        left = left_;
        right = right_;
        parent = parent_;
        value = value_;
    }

    Node(){
        Node(0, 0, 0, 0);
    }
};

int dfs(Node* root){
    if (root == nullptr) return 0;
    return max(dfs(root -> left) + 1, dfs(root -> right) + 1);
}

int32_t main(){
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    vector< pair<int, pair<int, int> > > tree;
    int n; cin >> n;
    vector<Node*> nodes(n);
    for (int i = 0; i < n; i ++) nodes[i] = new Node();
    for (int i = 0; i < n; i ++){
        int v, l, r;
        cin >> v >> l >> r;
        l --; r --;
        tree.push_back({v, {l, r}});
        nodes[i] -> value = v;

        if (l != -1){
            nodes[i] -> left = nodes[l];
            nodes[l] -> parent = nodes[i];
        }
        else {
            nodes[i] -> left = nullptr;
        }

        if (r != -1){
            nodes[i] -> right = nodes[r];
            nodes[r] -> parent = nodes[i];
        }
        else {
            nodes[i] -> right = nullptr;
        }
    }

    Node* root = nullptr;

    for (int i = 0; i < n; i ++){
        if (nodes[i] -> parent == nullptr){
            root = nodes[i];
            break;
        }

    }

    cout << dfs(root) << endl;
}
/*
6
-2 0 2
8 4 3
9 0 0
3 5 6
0 0 0
6 0 0
*/

