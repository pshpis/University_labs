#include <bits/stdc++.h>

using namespace std;

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

int main()
{
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    DoubleList<int> a;

    string s;
    while (cin >> s){
        int n = s.size();
        bool is_ans = false;
        for (int i = 0; i < n; i ++){
            if (s[i] == '('){
                a.push_back(1);
            }

            if (s[i] == '['){
                a.push_back(2);
            }

            if (s[i] == ')'){
                if (a.size() == 0 || a.back() != 1){
                    cout << "NO\n";
                    is_ans = true;
                    break;
                }
                a.pop_back();
            }

            if (s[i] == ']'){
                if (a.size() == 0 || a.back() != 2){
                    cout << "NO\n";
                    is_ans = true;
                    break;
                }
                a.pop_back();
            }
        }
        if (!is_ans){
            if (a.size() > 0) cout << "NO\n";
            else cout << "YES\n";
        }
        a.clear();
    }
}


