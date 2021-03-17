#ifndef array_int_was_declarated
#define array_int_was_declarated

struct array_uint{
    unsigned int* arr;
    unsigned int size;
};

struct array_uint new_array(){
    struct array_uint res;
    res.size = 0;
    res.arr = NULL;
    return res;
}

struct array_uint reserve(unsigned int sz){
    struct array_uint res;
    res.size = sz;
    res.arr = (unsigned int*)malloc(sz*sizeof(unsigned int));
    return res;
}

void push_back(unsigned int x, struct array_uint* a){
    a->size ++;
    a->arr = (unsigned int*)realloc(a->arr, a->size * sizeof(unsigned int));
    *(a->arr + (a->size - 1)) = x;
}

unsigned int get(unsigned int i, struct array_uint* a){
    return *(a->arr + i);
}

void set(unsigned int i, unsigned int x, struct array_uint* a){
    *(a->arr + i) = x;
}


#endif
