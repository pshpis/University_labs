#include <bits/stdc++.h>

using namespace std;

#define int int64_t
#define endl "\n"

int inf = 1e18;

class Node{
public:
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    int value;
    int cnt;

    Node(int value_, Node* left_, Node* right_, Node* parent_){
        left = left_;
        right = right_;
        parent = parent_;
        value = value_;
    }

    Node(int value_, Node* parent_){
        value = value_;
        parent = parent_;
        left = nullptr;
        right = nullptr;
    }

    Node(int value_){
        value = value_;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    Node(){
        Node(0, 0, 0, 0);
    }
};

int dfs(Node*& root){
    if (root == nullptr) return 0;
    return max(dfs(root -> left) + 1, dfs(root -> right) + 1);
}

bool correct(Node*& root, int min_v, int max_v){
    if (root == nullptr) return true;
    return (root->value > min_v && root->value < max_v && correct(root -> left, min_v, root->value) && correct(root -> right, root-> value, max_v));

}

Node* find(Node*& root, int v){
    if (root == nullptr) return nullptr;
    if (root -> value == v) return root;
    if (root -> value > v) find(root -> left, v);
    else find(root -> right, v);
}

void add(Node*& root, int v){
    if (root == nullptr){
        root = new Node(v);
//        cout << root->value << endl;
        return;
    }

    if (v == root -> value){
            root -> cnt ++;
        return;
    }

    if (v < root->value){
        if (root -> left == nullptr) root->left = new Node(v, root);
        else add(root->left, v);
    }

    if (v > root -> value){
        if (root -> right == nullptr) root->right = new Node(v, root);
        else add(root->right, v);
    }
}

Node* min(Node* root){
    if (root -> left == nullptr) return root;
    return min(root->left);
}

Node* max(Node* root){
    if (root -> right == nullptr) return root;
    return max(root->right);
}

Node* next(Node* root, int x){
    Node* cur = root;
    Node* tmp = nullptr;
    while (cur != nullptr){
        if (cur -> value > x){
            tmp = cur;
            cur = cur -> left;
        }
        else {
            cur = cur -> right;
        }
    }
    return tmp;
}

Node* prev(Node* root, int x){
    Node* cur = root;
    Node* tmp = nullptr;

    while (cur != nullptr){
        if (cur -> value < x){
            tmp = cur;
            cur = cur -> right;
        }
        else {
            cur = cur -> left;
        }
    }
    return tmp;
}

Node* del(Node* root, int x){
    if (root == nullptr) return root;

    if (root->value > x){
        root->left = del(root->left, x);
        return root;
    }

    if (root->value < x){
        root->right = del(root->right, x);
        return root;
    }

    if (root -> cnt > 1){
        root -> cnt --;
        return;
    }

    if (root->left != nullptr && root->right !=nullptr){
        root->value = min(root->right) -> value;
        root->right = del(root->right, root->value);
        return root;
    }

    if (root->left != nullptr) root = root -> left;
    else if (root->right != nullptr) root = root-> right;
    else root = nullptr;

    return root;

}


void write(Node* root){
    if (root != nullptr){
        write(root->left);
        cout << root -> value << " ";
        write(root -> right);
    }
}

int32_t main(){
    freopen("bstsimple.in", "r", stdin);
    freopen("bstsimple.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);


    string s;
    Node* root = nullptr;
    while (cin >> s){
        int x; cin >> x;
        if (s == "insert"){
            add(root, x);
        }
        if (s == "exists"){
            if (find(root, x) != nullptr) cout << "true" << endl;
            else cout << "false" << endl;
        }
        if (s == "next"){
            Node* a = next(root, x);
            if (a == nullptr) cout << "none" << endl;
            else cout << a -> value << endl;
        }
        if (s == "prev"){
            Node* a = prev(root, x);
            if (a == nullptr) cout << "none" << endl;
            else cout << a -> value << endl;
        }
        if (s == "delete"){
            root = del(root, x);
        }
        if (s == "write"){
            cout << "Root is " << root->value << endl;
            write(root);
            cout << endl;
        }
    }
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



