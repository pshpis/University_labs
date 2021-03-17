#ifndef pair_was_declarated
#define pair_was_declarated

#define type unsigned int

struct pair{
    type first;
    type second;
};

struct pair new_pair(type f, type s){
    struct pair res;
    res.first = f;
    res.second = s;
    return res;
}

int pair_cmp(const struct pair *a, const struct pair *b){
    if (a->first > b->first) return 1;
    if (a->first < b->first) return -1;
    if (a->first == b->first){
//        if (a.second > b.second) return 1;
//        if (a.second < b.second) return -1;
        return 0;
    }
}

#endif
