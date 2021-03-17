#include <bits/stdc++.h>

using namespace std;

queue<unsigned short> q;
vector<string> comands;
vector<unsigned short> reg(26, 0);
vector<pair<string, unsigned short> > labels;

unsigned short get(){
    unsigned short res = q.front();
    q.pop();
    return res;
}

void put(unsigned short x){
    q.push(x);
}

void read_comands(){
    string s;
    while (cin >> s){
        comands.push_back(s);
    }
}

void make_labels(){
    for (int i = 0; i < comands.size(); i ++){
        string s = comands[i];
        if (s[0] == ':'){
            labels.push_back({s.substr(1, s.size() - 1), i});
        }
    }
}

int main(){
//    freopen("quack.in", "r", stdin);
//    freopen("quack.out", "w", stdout);


    read_comands();
    make_labels();

    int i = 0;

    while (i < comands.size()){
        if (comands[i] == ""){
            i ++;
            continue;
        }

        char c = comands[i][0];
        unsigned short a, b;
        string tmp;

        switch(c){
        case '+':
            a = get(); b = get();
            put(a + b);
            break;
        case '-':
            a = get();
            b = get();
            put(a - b);
            break;
        case '*':
            a = get();
            b = get();
            put(a * b);
            break;
        case '/':
            a = get();
            b = get();
            if (b == 0) put(0);
            else put(a/b);
            break;
        case '%':
            a = get();
            b = get();
            if (b == 0) put(0);
            else put(a % b);
            break;
        case '>':
            reg[comands[i][1]-'a'] = get();
            break;
        case '<':
            put(reg[comands[i][1]-'a']);
            break;
        case 'P':
            if (comands[i].size() == 1){
                cout << get() << endl;
            }
            else {
                cout << reg[comands[i][1] - 'a'] << endl;
            }
            break;
        case 'C':
            if (comands[i].size() == 1){
                cout << (char)(get() % (256));
            }
            else {
                cout << (char)reg[comands[i][1] - 'a'];
            }
            break;
        case ':':
            break;
        case 'J':
            tmp = comands[i].substr(1, comands[i].size() - 1);
            for (int j = 0; j < labels.size(); j ++){
                if (labels[j].first == tmp){
                    i = labels[j].second - 1;
                    break;
                }
            }
            break;
        case 'Z':
            if (reg[comands[i][1] - 'a'] == 0){
                tmp = comands[i].substr(2, comands[i].size() - 1);
                for (int j = 0; j < labels.size(); j ++){
                    if (labels[j].first == tmp){
                        i = labels[j].second - 1;
                        break;
                    }
                }
            }
            break;
        case 'E':
            if (reg[comands[i][1] - 'a'] == reg[comands[i][2] - 'a']){
                tmp = comands[i].substr(3, comands[i].size() - 1);
                for (int j = 0; j < labels.size(); j ++){
                    if (labels[j].first == tmp){
                        i = labels[j].second - 1;
                        break;
                    }
                }
            }
            break;
        case 'G':
            if (reg[comands[i][1] - 'a'] > reg[comands[i][2] - 'a']){
                tmp = comands[i].substr(3, comands[i].size() - 1);
                for (int j = 0; j < labels.size(); j ++){
                    if (labels[j].first == tmp){
                        i = labels[j].second - 1;
                        break;
                    }
                }
            }
            break;
        case 'Q':
            return 0;
        default:
            put(stoi(comands[i]));
            break;
        }
        i ++;
    }

}
/*
0
>a
Zaend
100
100
+
:end
P
*/
