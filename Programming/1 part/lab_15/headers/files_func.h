#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


int fseek_filesize(const char *filename){
    FILE *fp = NULL;
    long off;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("failed to fopen %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fseek(fp, 0, SEEK_END) == -1)
    {
        printf("failed to fseek %s\n", filename);
        exit(EXIT_FAILURE);
    }

    off = ftell(fp);
    if (off == (long)-1)
    {
        printf("failed to ftell %s\n", filename);
        exit(EXIT_FAILURE);
    }

//    printf("[*] fseek_filesize - file: %s, size: %ld\n", filename, off);

    if (fclose(fp) != 0)
    {
        printf("failed to fclose %s\n", filename);
        exit(EXIT_FAILURE);
    }

    return off;
}

struct array_uint get_file_as_array(char *file_name){
    FILE* file_in = fopen(file_name, "rb");

    struct array_uint res = new_array();

    unsigned int sym;
    if (file_in == NULL){
        return res;
    }
    else {
        int i = 0;
        int fsize = fseek_filesize(file_name);
        while ((sym = (unsigned char)fgetc(file_in)) != EOF && i < fsize){
            push_back(sym, &res);
            i ++;
        }
    }

    fclose(file_in);

    return res;
}

#endif
