#include <bits/stdc++.h>

using namespace std;

#define int int64_t

template<typename type>

class DoubleList
{
public:
    DoubleList()
    {
        Size=0;
        first=nullptr;
        last=nullptr;
    }

    ~DoubleList()
    {
        clear();
    }

    void push_back(type el)
    {
        if (first==nullptr)
        {
            first =new Node<type>(el);
            last = first;
        }
        else
        {
            Node<type>* curr=last;
            (*curr).Next=new Node<type>(el, curr);
            last=(*curr).Next;
        }
        Size++;
    }

    void push_front(type el)
    {
        if (first==nullptr)
            first =new Node<type>(el);
        else
        {
            Node<type> *curr=first;
            first=new Node<type>(el, nullptr, first);
            (*curr).Prev=first;
        }
        Size++;
    }

    DoubleList(vector<type> el)
    {
        Size=0;
        first=nullptr;
        last=nullptr;
        for (int i=0; i<el.size(); i++)
            push_back(el[i]);
    }


    int size()
    {
        return Size;
    }

    bool find(type el)
    {
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

    int count(type el)
    {
        int result=0;
        if (Size==0) return result;
        Node<type>* curr=first;
            while ((*curr).Next!=nullptr)
            {
                if ((*curr).Data==el) result++;
                curr=(*curr).Next;
            }
        if ((*curr).Data==el) result++;
        return result;
    }

    type& operator[](const int& pl)
    {
        Node<type> *curr;
        if (pl<Size/2)
        {
            curr=first;
            for (int i=0; i<pl; i++)
                curr=(*curr).Next;
        }
        else
        {
            curr=last;
            for (int i=Size; i>pl; i--)
                curr=(*curr).Prev;
        }
        return (*curr).Data;
    }

    void pop_front()
    {
        if (Size==0) return;
        Node<type>* temp=first;
        first=(*first).Next;
        delete temp;
        if (Size>0) Size--;
    }

    void pop_back()
    {
        if (Size==1) pop_front();
        if (Size==0) return;
        Node<type>* temp=last;
        last=(*last).Prev;
        (*last).Next=nullptr;
        delete temp;
        if (Size>0) Size--;
    }


    void clear()
    {
        if (Size==0) return;
        while (Size>0)
            pop_front();
    }

    void output()
    {
        if (Size==0) return;
        Node<type>* curr=first;
        while ((*curr).Next!=nullptr)
        {
            cout<<(*curr).Data<<" ";
            curr=(*curr).Next;
        }
        cout<<(*curr).Data<<endl;
    }

    void rev_output()
    {
        if (Size==0) return;
        Node<type>* curr=last;
        while ((*curr).Prev!=nullptr)
        {
            cout<<(*curr).Data<<" ";
            curr=(*curr).Prev;
        }
        cout<<(*curr).Data<<endl;

    }

    type back()
    {
        return (*last).Data;
    }

    type front()
    {
        return (*first).Data;
    }


private:
    template<typename type_>
    class Node
    {
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

    Node<type> *first = nullptr;
    Node<type> *last = nullptr;
    int Size = 0;

};

int parse_int(string s){
    if (s[0] == '-'){
        int res = 0;
        for (int i = 1; i < s.size(); i ++){
            res *= 10;
            res += s[i] - '0';
        }
        return -res;
    }

    int res = 0;
    for (int i = 0; i < s.size(); i ++){
        res *= 10;
        res += s[i] - '0';
    }
    return res;
}

int32_t main()
{
    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    DoubleList<int> a;

    string s;
    while (cin >> s){
        if (s != "*" && s != "+" && s != "-"){
            a.push_back(parse_int(s));
        }
        else if (s == "*"){
            int x1 = a.back();
            a.pop_back();
            int x2 = a.back();
            a.pop_back();
            a.push_back(x1 * x2);

//            a.output();
        }
        else if (s == "+"){
            int x1 = a.back();
            a.pop_back();
            int x2 = a.back();
            a.pop_back();
            a.push_back(x1 + x2);

//            a.output();
        }
        else if (s == "-"){
            int x1 = a.back();
            a.pop_back();
            int x2 = a.back();
            a.pop_back();
            a.push_back(x2 - x1);

//            a.output();
        }
    }
    cout << a.back();
}



