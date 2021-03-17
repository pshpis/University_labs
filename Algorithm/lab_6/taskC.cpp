#include <bits/stdc++.h>

using namespace std;

#define int int64_t
#define endl "\n"

template<typename T1, typename T2>
class LinkedMapNode{
public:
    T1 key;
    T2 value;

    LinkedMapNode<T1, T2>* prev;
    LinkedMapNode<T1, T2>* next;

    LinkedMapNode<T1, T2>* added_before;
    LinkedMapNode<T1, T2>* added_after;

    LinkedMapNode(T1 k, T2 v, LinkedMapNode<T1, T2>* p, LinkedMapNode<T1, T2>* b):
        key(k), value(v), prev(p), added_before(b)
    {
        next = nullptr;
        added_after = nullptr;
    }

};

template <typename T>
string toString(T val)
{
    ostringstream oss;
    oss << val;
    return oss.str();
}

template<typename T>
int HashFunctionHorner(const T& value, const int table_size, const int hash_key){
    string s = toString<T>(value);
    int hash = 0;
    for (int i = 0; i < s.size(); i ++) hash = (hash_key * hash + s[i]) % table_size;
    hash = (hash * 2 + 1) % table_size;
    return hash;
}

template<typename T1, typename T2>
class LinkedMap{
public:
    int default_table_size = 1e5;
    int default_hash_key = 1e5 + 19;

    int table_size;
    int hash_key;

    vector<LinkedMapNode<T1, T2>* > table;

    LinkedMapNode<T1, T2>* last_added;


    LinkedMap(){
        table_size = default_table_size;
        hash_key = default_hash_key;
        last_added = nullptr;

        table = vector<LinkedMapNode<T1, T2>* >(table_size);
        for (int i = 0; i < table_size; i ++) table[i] = nullptr;
    }

    bool insert(T1 key, T2 value){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);
//        cout << hash << endl;
        if (find(key)) return false;

        LinkedMapNode<T1, T2>* nw = new LinkedMapNode<T1, T2>(key, value, table[hash], last_added);

//        cout << "I created new Node" << endl;

        if (table[hash] != nullptr){
            table[hash] -> next = nw;
        }

//        cout << "xxx" << endl;

        if (last_added != nullptr){
            last_added -> added_after = nw;
        }

//         cout << "xxx" << endl;

        table[hash] = nw;
        last_added = nw;

//        cout << "I insert new node" << endl;

        return true;
    }

    bool find(T1 key){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        LinkedMapNode<T1, T2>* tmp = table[hash];

        while (tmp != nullptr){
            if (tmp -> key == key) return true;
            tmp = tmp -> prev;
        }

        return false;
    }

    LinkedMapNode<T1, T2>* get(T1 key){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        LinkedMapNode<T1, T2>* tmp = table[hash];

        while (tmp != nullptr){
            if (tmp -> key == key) return tmp;
            tmp = tmp -> prev;
        }

        return nullptr;
    }

    bool remove(T1 key){
        if (!find(key)) return false;

        LinkedMapNode<T1, T2>* tmp = get(key);

//        if (tmp == nullptr) cout << "Shit" << endl;

//        cout << "I am removing" << endl;

        if (tmp -> added_before != nullptr){
            tmp -> added_before -> added_after = tmp -> added_after;
        }

        if (tmp -> added_after != nullptr){
            tmp -> added_after -> added_before = tmp -> added_before;
        }

//        cout << "I am removing" << endl;

        if (tmp -> prev != nullptr){
            tmp -> prev -> next = tmp -> next;
        }

//        cout << "I am removing" << endl;

        if (tmp -> next != nullptr){
//            cout << "I am in if" << endl;
            cout << tmp -> next -> key << endl;
            tmp -> next -> prev = tmp -> prev;
        }



        delete tmp;

        return true;
    }

    LinkedMapNode<T1, T2>* added_after(T1 key){
        LinkedMapNode<T1, T2>* tmp = get(key);
        tmp = tmp -> added_after;
        return tmp;
    }

    LinkedMapNode<T1, T2>* added_before(T1 key){
        LinkedMapNode<T1, T2>* tmp = get(key);
        tmp = tmp -> added_before;
        return tmp;
    }
};

int32_t main(){
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    ios::sync_with_stdio(false);

    LinkedMap<string, string> t;

    string s;
    while (cin >> s){
        if (s == "put"){
            string x, y;
            cin >> x >> y;
            t.insert(x, y);
        }

        if (s == "get"){
            string x;
            cin >> x;
            if (!t.find(x)) cout << "none" << endl;
            else cout << t.get(x) -> value << endl;
        }

        if (s == "delete"){
            string x;
            cin >> x;
            t.remove(x);
        }

        if (s == "prev"){
            string x;
            cin >> x;

            LinkedMapNode<string, string>* tmp = t.added_before(x);
            if (tmp == nullptr) cout << "none" << endl;
            else cout << tmp -> value << endl;
        }

        if (s == "next"){
            string x;
            cin >> x;

            LinkedMapNode<string, string>* tmp = t.added_after(x);
            if (tmp == nullptr) cout << "none" << endl;
            else cout << tmp -> value << endl;
        }

    }

}

/*
put a a
195
put b b
197
put c c
199
put d d
201
put abs abs

*/
