#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define int int64_t

class TreeNode{
public:

    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    int value;

    int height;

    TreeNode(TreeNode* par = nullptr, int v = 0, int h = 1, TreeNode* l = nullptr, TreeNode* r = nullptr):
        parent(par), left(l), right(r), value(v), height(h)
    {}
};

int height(TreeNode* t){
    if (t == nullptr) return 0;
    return t -> height;
}

int balance(TreeNode* t){
    if (t == nullptr) return 0;
    return height(t -> right) - height(t -> left);
}

int dfs(TreeNode* t){
    if (t == nullptr) return 0;
    t -> height = max(dfs(t -> left), dfs(t -> right)) + 1;
    return t -> height;
}

void fix_height(TreeNode* p){
    if (p == nullptr) return;
	int h1 = height(p -> left);
	int h2 = height(p -> right);
	p -> height = (h1 > h2 ? h1 : h2) + 1;
}

TreeNode* rotate_left(TreeNode* a){
    TreeNode* b = a -> right;
    a -> right = b -> left;
    b -> left = a;
    fix_height(a);
    fix_height(b);
    return b;
}

TreeNode* rotate_right(TreeNode* a){
    TreeNode* b = a -> left;
    a -> left = b -> right;
    b -> right = a;
    fix_height(a);
    fix_height(b);
    return b;
}

TreeNode* big_rotate_left(TreeNode* a){
    a -> right = rotate_right(a -> right);
    return rotate_left(a);
}

TreeNode* big_rotate_right(TreeNode* a){
    a -> left = rotate_left(a -> left);
    return rotate_right(a);
}

TreeNode* fix_balance(TreeNode* p){
    if (p == nullptr) return nullptr;
    fix_height(p);
    if (balance(p) == 2){
        if (balance(p -> right) < 0) p -> right = rotate_right(p -> right);
        return rotate_left(p);
    }
    if (balance(p) == -2){
        if (balance(p -> left) > 0) p -> left = rotate_left(p -> left);
        return rotate_right(p);
    }
    return p;
}

void write(TreeNode* s){
    if (s == nullptr) return;
    queue<TreeNode*> q;
    q.push(s);

    int cnt = 1;
    while (!q.empty()) {
        TreeNode* v = q.front();
        q.pop();
        if (v == nullptr) break;
        int l = 0;
        int r = 0;

        if (v -> left != nullptr) {
            q.push(v -> left);
            l = ++ cnt;
        }

        if (v -> right != nullptr) {
            q.push(v -> right);
            r = ++ cnt;
        }

        cout << v -> value << " " << l << " " << r << endl;
    }
}

TreeNode* insert(TreeNode* root, int k, TreeNode* from = nullptr){
	if (root == nullptr) return new TreeNode(from, k);
	if (k < root -> value) root -> left = insert(root -> left, k, root);
	else root -> right = insert(root -> right, k, root);
	return fix_balance(root);
}

TreeNode* get_max(TreeNode* root){
    if (root -> right == nullptr) return root;
    return get_max(root -> right);
}

TreeNode* remove_max(TreeNode* root){
    if (root -> right == nullptr) return root -> left;
    root -> right = remove_max(root -> right);
    return fix_balance(root);
}

TreeNode* remove(TreeNode* root, int k){
    if (root == nullptr) return nullptr;
    if (root -> value == k && root -> left == nullptr && root -> right == nullptr){
        delete root;
        return nullptr;
    }
    if (k < root -> value) root -> left =  remove(root -> left, k);
    else if (k > root -> value) root -> right = remove(root -> right, k);
    else {
        TreeNode* left = root -> left;
		TreeNode* right = root -> right;
		delete root;
		if (left == nullptr) return right;
		if (right == nullptr) return left;
		TreeNode* mx = get_max(left);
		mx -> left = remove_max(left);
		mx -> right = right;
		return fix_balance(mx);
    }

    return fix_balance(root);
}

TreeNode* find(TreeNode* root, int k){
    if (root == nullptr) return nullptr;
    if (root -> value == k) return root;
    if (k < root -> value) return find(root -> left, k);
    else return find(root -> right, k);
}

int32_t main(){
    freopen("avlset.in", "r", stdin);
    freopen("avlset.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    ios::sync_with_stdio(false);

    int n; cin >> n;

    TreeNode* root = nullptr;
    char c;
    int i = 0;
    while (i < n){
        cin >> c;
        int x; cin >> x;
        if (c == 'A'){
            if (find(root, x) == nullptr) root = insert(root, x);
            cout << balance(root) << endl;
        }
        if (c == 'D'){
            if (find(root, x) != nullptr) root = remove(root, x);
            cout << balance(root) << endl;
        }
        if (c == 'C'){
            if (find(root, x) == nullptr) cout << "N" << endl;
            else cout << "Y" << endl;
        }
        i ++;
    }
}
