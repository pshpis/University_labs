#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct array{
    unsigned char* arr;
    unsigned long long size;
};

struct array new_array(){
    struct array res;
    res.size = 0;
    res.arr = NULL;
    return res;
}

struct array reserve(unsigned long long sz){
    struct array res;
    res.size = sz;
    res.arr = (unsigned char*)malloc(sz*sizeof(unsigned char));
    return res;
}

void push_back(unsigned char x, struct array* a){
    a->size ++;
    a->arr = (unsigned char*)realloc(a->arr, a->size * sizeof(unsigned char));
    *(a->arr + (a->size - 1)) = x;
}

unsigned char get(unsigned long long i, struct array* a){
    return *(a->arr + i);
}

void set(unsigned long long i, unsigned char x, struct array* a){
    *(a->arr + i) = x;
}

struct FanoNode{
    unsigned long long frequency;
    unsigned char character;
    struct FanoNode *left, *right;
};

unsigned long long array_size(struct FanoNode **array){
    return sizeof(array)/sizeof(struct FanoNode*);
}

void merge(struct FanoNode **left_array, struct FanoNode **right_array, struct FanoNode **result){
    unsigned long long left = 0, right = 0;
    unsigned long long left_size = array_size(left_array);
    unsigned long long right_size = array_size(right_array);

    result = malloc((left_size + right_size) * sizeof(struct FanoNode*));

    for (unsigned long long i = 0; i < left_size + right_size; i ++) {
        if ((left < left_size) && (right < right_size)) {
            if (left_array[left] -> frequency >= right_array[right] -> frequency) {
                result[i] = left_array[left];
                left ++;
            } else {
                result[i] = right_array[right];
                right ++;
            }
        } else if (left == left_size) {
            result[i] = right_array[right];
            right ++;
        } else if (right == right_size) {
            result[i] = left_array[left];
            left ++;
        }
    }
}

void merge_sort(struct FanoNode **array) {
    unsigned long long size = array_size(array);
    if (size == 1) return;

    unsigned long long divide_id = size / 2;
    struct FanoNode **left_array = malloc(divide_id * sizeof(struct FanoNode*));
    struct FanoNode **right_array = malloc((size - divide_id) * sizeof(struct FanoNode*));

    for (int i = 0; i < divide_id; i++) {
        left_array[i] = array[i];
    }
    for (int i = divide_id; i < size; i++) {
        right_array[i - divide_id] = array[i];
    }

    merge_sort(left_array);
    merge_sort(right_array);

    merge(left_array, right_array, array);
}

struct FanoNode *unite_nodes(struct FanoNode *left, struct FanoNode *right) {
    struct FanoNode *res = malloc(sizeof(struct FanoNode));

    res -> left = left;
    res -> right = right;

    res -> frequency = left -> frequency + right -> frequency;
    res -> character = -1;

    return res;
}

void make_code(struct FanoNode *need_node, unsigned char *string, unsigned long long size, unsigned char **dictionary) { //Записываем для каждого закодированного символа строку 1 и 0
    if (need_node -> right == NULL) {
        strcpy((char *) dictionary[need_node -> character], (char *) string);
        return;
    }

    string[size + 1] = '\0';
    string[size] = '1';
    make_code(need_node -> right, string, size + 1, dictionary);

    string[size + 1] = '\0';
    string[size] = '0';
    make_code(need_node -> left, string, size + 1, dictionary);
}

void write_num_to_str(unsigned long long value, unsigned char *string, unsigned long long start, unsigned long long end) {
    for (unsigned long long i = 0; i < end; i++) {
        string[start + end - 1 - i] = value % 2 + '0';
        value /= 2;
    }
    string[start + end] = '\0';
}

unsigned long long reverse(unsigned long long value) { // reverse number
    unsigned long long buf = 0;

    for (unsigned long long i = 0; i < 8; i++) {
        buf = buf * 2 + value % 2;
        value /= 2;
    }

    return buf;
}

struct array encode(struct array bytes) {
    unsigned char* data = bytes.arr;
    unsigned long long data_size = bytes.size;

    unsigned char **dictionary = calloc(256, sizeof(unsigned char*));
    unsigned long long *freq = calloc(256, sizeof(unsigned long long));

    for (unsigned long long i = 0; i < 256; i ++){
        dictionary[i] = calloc(256, sizeof(unsigned char));
        strcpy((char*)dictionary[i], "");
        freq[i] = 0;
    }

    struct FanoNode **fano_tree = calloc(256, sizeof(struct FanoNode*));

    for (unsigned long long i = 0; i < data_size; i ++) freq[data[i]]++;

    unsigned long long cnt = 0;
    for (unsigned long long i = 0; i < 256; i ++){
        if (freq[i] != 0) {
            struct FanoNode *res = malloc(sizeof(struct FanoNode));

            res -> character = i;
            res -> frequency = freq[i];
            res -> left = NULL;
            res -> right = NULL;
            fano_tree[cnt ++] = res;
        }
    }

    unsigned long long letterCount = cnt;

    merge_sort(fano_tree);

    while (cnt != 1) {
        fano_tree[cnt - 2] = unite_nodes(fano_tree[cnt - 2], fano_tree[cnt - 1]);
        cnt --;
    }

    unsigned char *string = calloc(256, sizeof(unsigned char));
    unsigned long long size = 0;

    make_code(fano_tree[0], string, size, dictionary);

    unsigned char *res_data = calloc(data_size + letterCount + 1, sizeof(unsigned char));
    res_data[data_size + letterCount] = '\0';
    unsigned long long ptr = 0;

    res_data[ptr ++] = letterCount;

    for (unsigned long long i = 0; i < 256; i ++){
        if (freq[i] != 0) {
            unsigned long long bin_iter = 0, count = 0, length = strlen((char*)dictionary[i]);

            res_data[ptr ++] = i;
            res_data[ptr ++] = length;

            for (unsigned long long j = 0; j < length; j ++){
                bin_iter = bin_iter * 2 + (dictionary[i][j] - '0');// (dictionary[i][j] == '0' ? 0 : 1);
                count ++;

                if (count == 8) {
                    res_data[ptr ++] = bin_iter;

                    bin_iter = 0;
                    count = 0;
                }
            }
            if (count != 0) {
                res_data[ptr ++] = bin_iter;
            }
        }
    }

    unsigned long long bin_iter = 0, count = 0;

    for (unsigned long long i = 0; i < data_size; i ++){
        for (unsigned long long j = 0; dictionary[data[i]][j] != '\0'; j ++){
            bin_iter = bin_iter* 2 + (dictionary[data[i]][j] - '0');
            count ++;

            if (count == 8) {
                res_data[ptr ++] = bin_iter;

                bin_iter = 0;
                count = 0;
            }
        }
    }

    printf("Here\n");

    if (count != 0){
        res_data[ptr ++] = bin_iter << (8 - count);
    }

    res_data[ptr ++] = 8 - count;
    res_data[ptr ++] = '\0';

    for (int i = 0; i < 256; i ++){
        free(dictionary[i]);
        free(fano_tree[i]);
    }

    free(dictionary);
    free(fano_tree);
    free(freq);
    free(string);

    data_size = ptr;


    printf("%d\n", ptr);

    res_data = realloc(res_data, ptr);

    printf("Here\n");

    struct array res;
    res.arr = res_data;
    res.size = data_size;

    printf("Here\n");

    return res;
}

struct array decode(struct array bytes){
    unsigned char *data = bytes.arr;
    unsigned long long data_size = bytes.size;
    printf("%d\n", data_size);

    unsigned char **dictionary = calloc(256, sizeof(unsigned char *));
    for (unsigned long long i = 0; i < 256; i ++)
        dictionary[i] = calloc(256, sizeof(unsigned char));

    unsigned long long alph_size = (unsigned long long) data[0];
    unsigned long long ptr = 1;

    for (unsigned long long i = 0; i < alph_size; i ++){
        unsigned long long value = data[ptr ++], size = data[ptr ++];

        for (unsigned long long j = 0; j < size / 8; j ++){
            unsigned long long buf = data[ptr ++];

            write_num_to_str(buf, dictionary[value], 8 * j, 8);
        }
        if (size % 8 != 0) {
            unsigned long long buf = data[ptr++];

            write_num_to_str(buf, dictionary[value], (size / 8) * 8, size % 8);
        }
    }

    unsigned char *string = calloc(256, sizeof(unsigned char));
    unsigned char *res_data = calloc(data_size - ptr + 1, sizeof(unsigned char));

//    res_data[data_size - ptr] = '\0';
    printf("%d\n", data_size);
    printf("%d\n",  ptr);
    printf("%d\n", data_size - ptr + 1);
    unsigned long long count = 0;
    unsigned long long i = ptr;
    ptr = 0;


    for (; i < data_size; i ++) {
        unsigned long long x = reverse(data[i]);
        for (unsigned long long j = 0; j < 8; j++) {
            string[count ++] = (x % 2) + '0';
            string[count] = '\0';
            x /= 2;
            for (unsigned long long iter = 0; iter < 256; iter ++){
                if (strcmp((char*)string, (char*)dictionary[iter]) == 0){
                    res_data[ptr ++] = iter;
                    count = 0;
                    strcpy((char *) string, "");
                    break;
                }
            }
        }
    }
    unsigned long long x = reverse(data[data_size - 2]);

    printf("Here\n");
    for (unsigned long long i = 0; i < 8 - (data[data_size - 1] % 8); i ++){
        string[count ++] = (x % 2) + '0';
        string[count] = '\0';

        x /= 2;
        printf("%d\n", i);
        for (unsigned long long iter = 0; iter < 256; iter ++){
            printf("%d\n", iter);
            if (strcmp((char *) string, (char *) dictionary[iter]) == 0){
                printf("%d\n", iter);
                res_data[ptr++] = iter;
                printf("%d\n", iter);
                count = 0;
                strcpy((char *) string, "");

                break;
            }
        }

    }

    printf("Here\n");

    for (i = 0; i < 256; i++) free(dictionary[i]);
    free(dictionary);
    free(string);
    data_size = ptr;

    struct array res;
    res.arr = res_data;
    res.size = data_size;

    printf("Decoding finished!!!!\n");

    return res;
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

long long fseek_filesize(const char *filename){
    FILE *fp = NULL;
    long off;

    fp = fopen(filename, "rb");
    if (fp == NULL){
        printf("failed to fopen %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fseek(fp, 0, SEEK_END) == -1){
        printf("failed to fseek %s\n", filename);
        exit(EXIT_FAILURE);
    }

    off = ftell(fp);
    if (off == (long)-1){
        printf("failed to ftell %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fclose(fp) != 0){
        printf("failed to fclose %s\n", filename);
        exit(EXIT_FAILURE);
    }

    return off;
}

struct array get_4bytes(long long a){
    struct array res = new_array();

    for (long long i = 0; i < 4; i ++){
        push_back(a % 256, &res);
        a /= 256;
    }

    return res;
}

long long get_from_4bytes(struct array* a){
    long long res = 0;
    for (long long i = 3; i >= 0; i --){
        res *= 256;
        res += get(i, a);
    }
    return res;
}


struct array get_file_as_array(char *file_name){
    FILE* file_in = fopen(file_name, "rb");

    struct array res = new_array();

    unsigned long long sym;
    if (file_in == NULL){
        return res;
    }
    else {
        long long i = 0;
        long long fsize = fseek_filesize(file_name);
        while ((sym = (unsigned char)fgetc(file_in)) != EOF && i < fsize){
            push_back(sym, &res);
            i ++;
        }
    }

    fclose(file_in);

    return res;
}

unsigned char get_char(unsigned long long x){
    return ' ' + (x - 32);
}

struct ArchiveFile{
    struct array bytes;
    char* name;
};

void write_file(struct ArchiveFile f){
    FILE* file_out = fopen(f.name, "a");
    fclose(file_out);
    file_out = fopen(f.name, "wb");

    for (long long i = 0; i < f.bytes.size; i ++){
        fputc(get(i, &f.bytes), file_out);
    }

    fclose(file_out);

    return;
}

struct ArchiveFile get_file(char* file_name){
    struct ArchiveFile res;
    res.name = file_name;
    res.bytes = get_file_as_array(file_name);
    return res;
}

void write_file_in_archive(struct ArchiveFile f, char* archive_name){
    f.bytes = encode(f.bytes);
    printf("HEEERE!!\n");
    FILE* file_out = fopen(archive_name, "ab");

    long long name_len = strlen(f.name);
    struct array name_len_4bytes = get_4bytes(name_len);

    for (long long i = 0; i < 4; i ++){
        fputc(get_char(get(i, &name_len_4bytes)), file_out);
    }

    printf("name len - %d\n", name_len);
    printf("name len bytes - %u %u %u %u\n", get(0, &name_len_4bytes), get(1, &name_len_4bytes), get(2, &name_len_4bytes), get(3, &name_len_4bytes));

    for (long long i = 0; i < name_len; i ++){
        fprintf(file_out, "%c", *(f.name + i));
    }

    struct array data_len_4bytes = get_4bytes(f.bytes.size);

    for (long long i = 0; i < 4; i ++){
        fputc(get_char(get(i, &data_len_4bytes)), file_out);
    }

    for (long long i = 0; i < f.bytes.size; i ++){
        fputc(get_char(get(i, &f.bytes)), file_out);
    }

    fclose(file_out);
}

long long archive_reading_index = 0;

struct ArchiveFile get_file_from_archive(char* archive_name){
    struct array all_bytes = get_file_as_array(archive_name);

    struct array name_len_4bytes = new_array();
    name_len_4bytes = reserve(4);
    for (long long j = 0; j < 4; j ++){
        set(j, get(archive_reading_index, &all_bytes), &name_len_4bytes);
        archive_reading_index ++;
    }

    long long name_len = get_from_4bytes(&name_len_4bytes);
    char* name = (char*)malloc((name_len + 1)*sizeof(char));
    *(name + name_len) = '\0';

    for (long long j = 0; j < name_len; j ++){
        *(name + j) = get_char(get(archive_reading_index, &all_bytes));
        archive_reading_index ++;
    }

    struct array bytes_len_4bytes = new_array();
    bytes_len_4bytes = reserve(4);
    for (long long j = 0; j < 4; j ++){
        set(j, get(archive_reading_index, &all_bytes), &bytes_len_4bytes);
        archive_reading_index ++;
    }

    long long bytes_len = get_from_4bytes(&bytes_len_4bytes);

    struct array bytes = new_array();
    bytes = reserve(bytes_len);

    for (long long j = 0; j < bytes_len; j ++){
        set(j, get(archive_reading_index, &all_bytes), &bytes);
        archive_reading_index ++;
    }

    struct ArchiveFile res;
    res.bytes = bytes;
    res.name = name;

    printf("BEFORE fucking decoding \n");

    res.bytes = decode(res.bytes);
    return res;
}

void extract(char* archive_name){
    struct array data = get_file_as_array(archive_name);
    long long i = 0;
    while (archive_reading_index < data.size){
        struct ArchiveFile f = get_file_from_archive(archive_name);
        write_file(f);
        i ++;
    }
}

void add(char* file_name, char* archive_name){
    struct ArchiveFile f = get_file(file_name);
    write_file_in_archive(f, archive_name);
}

void list(char* archive_name){
    struct array data = get_file_as_array(archive_name);
    long long i = 0;
    while (archive_reading_index < data.size){
        struct ArchiveFile f = get_file_from_archive(archive_name);
        printf("%s\n", f.name);
        i ++;
    }
    printf("%d\n", i);
}

#define debug_mode_2
int main(int argc, char** argv){
    printf("Archivator 2000 start work\n");
    #ifdef debug_mode_1
    argc = 5;
    argv[1] = "--file";
    argv[2] = "arch.arc";
    argv[3] = "--create";
    argv[4] = "in/file.txt";
    #endif
    #ifdef debug_mode_2
    argc = 4;
    argv[1] = "--file";
    argv[2] = "arch.arc";
    argv[3] = "--extract";
    #endif
    #ifdef debug_mode_3
    struct array test;
    push_back(10, &test);
    push_back(20, &test);
    test = encode(test);
    test = decode(test);
    printf("%d\n", get(0, &test));
    printf("%d\n", get(1, &test));

    return 0;
    #endif // debug_mode_3
    char* archive_name;
    for (long long i = 0; i < argc; i ++){
        if (strcmp(argv[i], "--file") == 0){
            archive_name = argv[i + 1];
            i ++;

            continue;
        }
        if (strcmp(argv[i], "--create") == 0){
            remove(archive_name);

            long long j = i + 1;
            while (j < argc){
                add(argv[j], archive_name);
                j ++;
            }
            i = j;
            continue;
        }

        if (strcmp(argv[i], "--extract") == 0){
            extract(archive_name);
        }

        if (strcmp(argv[i], "--list") == 0){
            list(archive_name);
        }

        if (strcmp(argv[i], "--size") == 0){
            printf("%d\n", fseek_filesize(archive_name));
        }

        if (strcmp(argv[i], "--bytes") == 0){
            struct array res = get_file_as_array(archive_name);
            for (long long i = 0; i < res.size; i ++){
                printf("%u\n", get(i, &res));
            }

            printf("%u -- first byte\n %u -- last byte\n", get(0, &res), get(res.size - 1, &res));
        }
    }
}
