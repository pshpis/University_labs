#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array_int.h"

#ifndef file_func_was_declarated
#define file_func_was_declarated

char* concat(char *s1, char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1);

    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);

    return result;
}

char* push_back_str(char c, char* str){
    size_t len = strlen(str);
    char *str2 = malloc(len + 1); /* one for extra char, one for trailing zero */
    strcpy(str2, str);
    str2[len] = c;
    return str2;
}

char* get_str(char c){
    char* res = malloc(1 * sizeof(char));
    *(res + 0) = c;
    return res;
}

struct array_int get_file_as_array(char *file_name){
    FILE* file_in = fopen(file_name, "r");

    struct array_int res = new_array();

    int sym;
    if (file_in == NULL){
//        printf("Error: Cann't read inner file");
    }
    else {
        while (1){
            sym = fgetc(file_in);
            if (sym == EOF){
                if (feof (file_in) != 0){
//                    printf ("\nFile reading ended\n");
                    break;
                }
                else{
//                    printf ("\nError: File reading error\n");
                    break;
                }
            }
            push_back(sym, &res);
        }
    }

    fclose(file_in);

    return res;
}

#endif
