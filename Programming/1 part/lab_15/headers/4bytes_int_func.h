#include <stdio.h>
#include <string.h>
#include "array_int.h"

#ifndef bytes_int_func_was_declarated
#define bytes_int_func_was_declarated

struct array_uint get_4bytes(int a){
    struct array_uint res = new_array();

    for (int i = 0; i < 4; i ++){
        push_back(a % 256, &res);
        a /= 256;
    }

    return res;
}

int get_from_4bytes(struct array_uint* a){
    int res = 0;
    for (int i = 3; i >= 0; i --){
        res *= 256;
        res += get(i, a);
    }
    return res;
}


#endif // 4bytes_int_func_was_declarated
