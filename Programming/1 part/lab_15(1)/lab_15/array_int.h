#ifndef array_int_was_declarated
#define array_int_was_declarated

struct array_int{
    int* arr;
    int size;
};

struct array_int new_array(){
    struct array_int res;
    res.size = 0;
    res.arr = NULL;
    return res;
}

struct array_int reserve(int sz){
    struct array_int res;
    res.size = sz;
    res.arr = (int*)malloc(sz*sizeof(int));
    return res;
}

void push_back(int x, struct array_int* a){
    a->size ++;
    a->arr = (int*)realloc(a->arr, a->size * sizeof(int));
    *(a->arr + (a->size - 1)) = x;
}

int get(int i, struct array_int* a){
    return *(a->arr + i);
}

void set(int i, int x, struct array_int* a){
    *(a->arr + i) = x;
}


#endif
