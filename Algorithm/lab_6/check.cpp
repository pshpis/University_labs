#include <bits/stdc++.h>

using namespace std;

#define int int64_t

template<typename type_>
class Node{
    public:
        Node *Next;
        Node *Prev;
        type_ Data;
        Node()=default;
        Node(type_ Data_, Node* Prev_=nullptr, Node* Next_=nullptr)
        {
            Data=Data_;
            Next=Next_;
            Prev=Prev_;
        }

    };

template<typename type>

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
            first =new Node<type>(el);
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
        }
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
class HashMultiMapTable{
public:
    int default_table_size = 1e7;
    int default_hash_key = 1e7 + 19;

    int table_size;
    int hash_key;

    HashSetTable<pair<T1, T2> > table;


public:
    HashMapTable(){
        table_size = default_table_size;
        hash_key = default_hash_key;
    }

    bool insert(T1 key, T2 value){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);
        if (!table.table[hash].find({key, value})){
            table.table[hash].push_back({key, value});
        }
    }

    bool find(T1 key){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        if (table.table[hash].size() != 0){
            Node< pair<T1, T2> >* curr = table.table[hash].first;

            while (curr != table.table[hash].last){
                if (curr -> Data.first == key) return true;
                curr = curr -> Next;
            }
            if (curr -> Data.first == key) return true;
        }

        return false;
    }

    vector<T2> get(T1 key){
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        vector<T2> res;
        if (table.table[hash].size() != 0){
            Node< pair<T1, T2> >* curr = table.table[hash].first;

            while (curr != table.table[hash].last){
                if (curr -> Data.first == key) res.push_back(curr -> Data.second);
                curr = curr -> Next;
            }
            if (curr -> Data.first == key) res.push_back(curr -> Data.second);
        }

        return res;
    }

    bool remove(T1 key, T2 value){
        if (!find(key)) return false;
        int hash = HashFunctionHorner<T1>(key, table_size, hash_key);

        pair<T1, T2> a = {key, value};
        return table.table[hash].remove(a);
    }

    bool removeall(T1 key){
        if (!find(key)) return false;
        vector<T2> vals = get(key);
        for (int i = 0; i < vals.size(); i ++) remove(key, vals[i]);
        return true;
    }


};

int32_t main(){
//    freopen("multimap.in", "r", stdin);
    freopen("multimap.in", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    ios::sync_with_stdio(false);


    for (int i = 0; i < 1e6; i ++){
        cout << "put " << i << " " << i + 100 << "\n";
        cout << "put " << i << " " << i + 200 << "\n";
    }
    cout << "get 10000\n";
}


