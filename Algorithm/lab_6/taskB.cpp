#include <bits/stdc++.h>

using namespace std;

#define int int64_t

template<class type_>
class Node{
public:
    Node<type_> *Next;
    Node<type_> *Prev;
    type_ Data;

    Node()=default;

    Node(type_ Data_, Node<type_>* Prev_ = nullptr, Node<type_>* Next_ = nullptr)
    {
        Data=Data_;
        Next=Next_;
        Prev=Prev_;
    }

};

template<class type>

class DoubleList{
public:
    DoubleList(){
        Size=0;
        first=nullptr;
        last=nullptr;
    }

    ~DoubleList(){
        clear();
    }

    void push_back(type el){
        if (first==nullptr){
            first = new Node<type>(el);
            last = first;
        }
        else{
            Node<type>* curr=last;
            (*curr).Next=new Node<type>(el, curr);
            last=(*curr).Next;
        }
        Size++;
    }

    void push_front(type el){
        if (first==nullptr)
            first =new Node<type>(el);
        else{
            Node<type> *curr=first;
            first=new Node<type>(el, nullptr, first);
            (*curr).Prev=first;
        }
        Size++;
    }

    DoubleList(vector<type> el){
        Size=0;
        first=nullptr;
        last=nullptr;
        for (int i=0; i<el.size(); i++)
            push_back(el[i]);
    }


    int size(){
        return Size;
    }

    bool find(type el){
        if (Size==0) return false;
        Node<type>* curr=first;
            while ((*curr).Next!=nullptr)
            {
                if ((*curr).Data==el) return true;
                curr=(*curr).Next;
            }
        if ((*curr).Data==el) return true;
        return false;
    }

    bool remove(type el){
        if (Size==0) return true;

        if (first -> Data == el){
            pop_front();
            return true;
        }

        if (last -> Data == el){
            pop_back();
            return true;
        }

        Node<type>* curr=first;
        while (curr -> Next != nullptr){
            if (curr -> Data == el){
                curr -> Prev -> Next = curr -> Next;
                curr -> Next -> Prev = curr -> Prev;
                delete curr;
                Size --;
                return true;
            }
            curr = curr -> Next;
        }

        if (curr -> Data == el){
            pop_back();
            return true;
        }
        return false;
    }

    int count(type el){
        int result=0;
        if (Size==0) return result;
        Node<type>* curr=first;
            while ((*curr).Next!=nullptr){
                if ((*curr).Data==el) result++;
                curr=(*curr).Next;
            }
        if ((*curr).Data==el) result++;
        return result;
    }

    type& operator[](const int& pl){
        Node<type> *curr;
        if (pl<Size/2){
            curr=first;
            for (int i=0; i<pl; i++)
                curr=(*curr).Next;
        }
        else{
            curr=last;
            for (int i=Size; i>pl; i--)
                curr=(*curr).Prev;
        }
        return (*curr).Data;
    }

    void pop_front(){
        if (Size==0) return;
        Node<type>* temp=first;
        first=(*first).Next;
        delete temp;
        if (Size>0) Size--;
    }

    void pop_back(){
        if (Size==1) pop_front();
        if (Size==0) return;
        Node<type>* temp=last;
        last=(*last).Prev;
        (*last).Next=nullptr;
        delete temp;
        if (Size>0) Size--;
    }


    void clear(){
        if (Size==0) return;
        while (Size>0)
            pop_front();
    }

    void output(){
        if (Size==0) return;
        Node<type>* curr=first;
        while ((*curr).Next!=nullptr){
            cout<<(*curr).Data<<" ";
            curr=(*curr).Next;
        }
        cout<<(*curr).Data<<endl;
    }

    void rev_output(){
        if (Size==0) return;
        Node<type>* curr=last;
        while ((*curr).Prev!=nullptr){
            cout<<(*curr).Data<<" ";
            curr=(*curr).Prev;
        }
        cout<<(*curr).Data<<endl;

    }

    type back(){
        return (*last).Data;
    }

    type front(){
        return (*first).Data;
    }


public:


    Node<type> *first = nullptr;
    Node<type> *last = nullptr;
    int Size = 0;

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

template <typename T>
class HashSetTable{
public:

    int default_table_size = 1e7;
    int default_hash_key = 1e7 + 19;

    int table_size;
    int hash_key;
    vector<DoubleList<T>> table;


public:
    HashSetTable(){
        table = vector<DoubleList<T>>(default_table_size);
        table_size = default_table_size;
        hash_key = default_hash_key;
    }

    bool insert(T value){
        int hash = HashFunctionHorner<T>(value, table_size, hash_key);
//        cout << hash << endl;
        if (!table[hash].find(value)){
            table[hash].push_back(value);
            return true;
        }

        return false;
    }

    bool find(T value){
        int hash = HashFunctionHorner<T>(value, table_size, hash_key);
        return table[hash].find(value);
    }

    bool remove(T value){
        int hash = HashFunctionHorner<T>(value, table_size, hash_key);
        return table[hash].remove(value);
    }

    T operator [](int hash){
        return table[hash];
    }
};

template <typename T1, typename T2>
class HashNode{
public:
    HashNode *next;
    HashNode *prev;

    T1 key;
    T2 value;

    HashNode(T1 key_, T2 value_, HashNode<T1, T2>* prev_ = nullptr, HashNode<T1, T2>* next_ = nullptr)
        :key(key_), value(value_), prev(prev_), next(next_)
    {}


    bool operator == (const HashNode& b){
        return key == b.key && value == b.value;
    }

    bool operator != (const HashNode& b){
        return !(key == b.key && value == b.value);
    }
};

template <typename T1, typename T2>
class HashMapTable{
public:

    int default_table_size = 1e7;
    int default_hash_key = 1e7 + 19;

    int table_size;
    int hash_key;
    vector<DoubleList<HashNode<T1, T2>>> table;

    HashNode<T1, T2>* last_added = nullptr;


public:
    HashMapTable(){
        table = vector<DoubleList<HashNode<T1, T2>>>(default_table_size);
        table_size = default_table_size;
        hash_key = default_hash_key;
    }

    bool find(T1 key){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        if (table[hash].size() != 0){
            Node<HashNode<T1, T2> >* curr = table[hash].first;

            while (curr != table[hash].last){
                if (curr -> Data.key == key) return true;
                curr = curr -> Next;
            }
            if (curr -> Data.key == key) return true;
        }

        return false;
    }

    bool insert(T1 key, T2 value){
        if (find(key)) return false;
        HashNode<T1, T2> *nw= new HashNode<T1, T2>(key, value, last_added);

        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);
        table[hash].push_back(*nw);

        if (last_added != nullptr) (*last_added).next = nw;
        last_added = nw;

        return true;
    }

    HashNode<T1, T2> get(T1 key){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        if (table[hash].size() != 0){
            Node<HashNode<T1, T2> >* curr = table[hash].first;

            while (curr != table[hash].last){
                if (curr -> Data.key == key) return curr -> Data;
                curr = curr -> Next;
            }
            if (curr -> Data.key == key) return curr -> Data;
        }
    }


    bool remove(T1 key){
        if (!find(key)) return false;
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        HashNode<T1, T2> a = get(key);
        return table[hash].remove(a);
    }


};

int32_t main(){
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    ios::sync_with_stdio(false);


    HashMapTable<string, string> t;

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
            else cout << t.get(x).value << endl;
        }

        if (s == "delete"){
            string x;
            cin >> x;
            t.remove(x);

        }

    }


}
