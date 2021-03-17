#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node
{
    int freq;
    unsigned char symb;
    struct Node *left, *right;
};

int reverse(int x){
    int ans = 0;
    for (int i = 0; i < 8; ++i)
    {
        ans = ans * 2 + x % 2;
        x /= 2;
    }
    return ans;
}


void write_num_to_str(int x, char* str, int k, int p){
    for (int i = 0; i < p; ++i)
    {
        str[k + p - 1 - i] = x % 2 + '0';
        x /= 2;
    }
    str[k + p] = '\0';
}

struct Node* join_nodes(struct Node* left, struct Node* right){
    struct Node* res = (struct Node*)malloc(sizeof(struct Node));
    res->right = right;
    res->left = left;
    res->freq = right -> freq + left -> freq;
    res->symb = -1;
    return res;
};

void merge(int leftSize, struct Node *leftArray[leftSize], int rightSize, struct Node *rightArray[rightSize],
           struct Node *result[leftSize + rightSize]) {
    int left = 0, right = 0;

    for (int i = 0; i < leftSize + rightSize; i ++) {
        if ((left < leftSize) && (right < rightSize)) {
            if (leftArray[left] -> freq >= rightArray[right] -> freq) {
                result[i] = leftArray[left];
                left ++;
            } else {
                result[i] = rightArray[right];
                right ++;
            }
        } else if (left == leftSize) {
            result[i] = rightArray[right];
            right++;
        } else if (right == rightSize) {
            result[i] = leftArray[left];
            left++;
        }
    }
}

void merge_sort(struct Node **array, int size) {
    if (size == 1) return;
    int divide_id = size / 2;
    struct Node *left_array[divide_id], *right_array[size - divide_id];
    for (int i = 0; i < divide_id; i ++) {
        left_array[i] = array[i];
    }
    for (int i = divide_id; i < size; i ++) {
        right_array[i - divide_id] = array[i];
    }
    merge_sort(left_array, divide_id);
    merge_sort(right_array, size - divide_id);
    merge(divide_id, left_array, size - divide_id, right_array, array);
}

char** dict;

void make_codes(struct Node* vertex, char* string, int str_len){
    if (vertex->right == NULL){
        strcpy(dict[(int)vertex -> symb], string);
        return;
    }
    string[str_len + 1] = '\0';
    string[str_len] = '1';
    make_codes(vertex->right, string, str_len + 1);
    string[str_len] = '0';
    make_codes(vertex->left, string, str_len + 1);
}

void compress(char* input_file_name){
    FILE* input_file = fopen (input_file_name, "rb");
    FILE* outputFile = fopen ("tmp.tmp", "wb");
    dict = malloc(256 * sizeof(char*));
    for (int i = 0; i < 256; ++i)
        dict[i] = calloc(256, sizeof(char));
    int* frequency = calloc(256, sizeof(int));
    int c, k = 0;
    struct Node** tree = malloc(256 * sizeof(struct Node*));
    while((c = getc(input_file)) != EOF)
		frequency[(unsigned char)c] ++;
	for (int i = 0; i < 256; i ++){
        if (frequency[i] != 0){
            struct Node *nw = malloc(sizeof(struct Node));
            nw -> symb = (unsigned char)i;
            nw -> freq = frequency[i];
            nw -> right = NULL;
            tree[k] = nw;
            k ++;
        }
    }
    int countOfLiters = k;
    merge_sort(tree, k);
    while (k != 1){
        merge_sort(tree, k);
        tree[k-2] = join_nodes(tree[k - 2], tree[k - 1]);
        k --;
    }
    char* string = (char*)calloc(256, sizeof(char));
    int strSize = 0;
    make_codes(tree[0], string, strSize);
    fseek(input_file, 0, SEEK_SET);
    putc(countOfLiters - 1, outputFile);
    for (int i = 0; i < 256; i ++){
        if (frequency[i] != 0){
            int count = 0, t = 0;
            putc(i, outputFile);
            int n = strlen(dict[i]);
            putc(n, outputFile);
            for(int j = 0; j < n; j ++){
                t = t * 2 + (dict[i][j] == '0' ? 0 : 1);
                count ++;
                if (count == 8){
                    count = 0;
                    putc (t, outputFile);
                    t = 0;
                }
            }
            if (count != 0){
                putc (t, outputFile);
            }
        }
    }
    int sum = 0, count = 0;
    while((c = getc(input_file)) != EOF){
        for (int i = 0; dict[c][i] != '\0'; i ++){
            sum = sum * 2 + (dict[c][i] - '0');
            count += 1;
            if (count == 8){
                putc ((char)sum, outputFile);
                count = 0;
                sum = 0;
            }
        }
	}
    if (count != 0){
        putc ((char)sum << (8 - count), outputFile);
    }
	putc (8 - count, outputFile);
	for (int i = 0; i < 256; i ++) free(dict[i]);
	free(dict);
    fclose(input_file);
    fclose(outputFile);
    remove(input_file_name);
    rename("tmp.tmp", input_file_name);
    return;
}

void decode(char* input_file_name){
    FILE* input_file = fopen(input_file_name, "rb");
    FILE* decoded_file = fopen("tmp.tmp", "wb");
    unsigned char** dict = (unsigned char**)malloc(256 * sizeof(unsigned char*));
    for (int i = 0; i < 256; i ++)
        dict[i] = (unsigned char*)malloc(256 + sizeof(char));
    int n = fgetc(input_file);
    n ++;
    for (int i = 0; i < n; i ++){
        int x = getc(input_file);
        int y = getc(input_file);
        for (int j = 0; j < y / 8; ++ j){
            int a = getc(input_file);
            write_num_to_str(a, dict[x], 8 * j, 8);
        }
        if (y % 8 != 0){
            int a = getc(input_file);
            write_num_to_str(a, dict[x], y / 8 * 8, y % 8);
        }
    }
    unsigned char* str = (unsigned char*)calloc(256, sizeof(char));
    int buff[2], t = 0;
    int c = getc(input_file);
    buff[1] = c;
    c = fgetc(input_file);
    while(1){
        buff[0] = buff[1];
        buff[1] = c;
        c = getc(archive);
        if (c == EOF) break;
		int x = (unsigned char)buff[0];
		x = reverse(x);
		for (int i = 0; i < 8; i ++){
            str[t] = (x % 2) + '0';
            t ++;
            str[t] = '\0';
            x /= 2;

            int q = 0;
            int p = 0;
            for (; p < 256; p ++) if (strcmp(dict[p], str) == 0){
                q = 1;
                break;
            }

            if (q){
                putc (p, decoded_file);
                t = 0;
                strcpy(str, "");
            }
        }
	}
    int x = (unsigned char)buff[0];
    x = reverse(x);
	for (int i = 0; i < 8 - (buff[1] % 8); i ++){
        str[t] = (x % 2) + '0';
        t ++;
        str[t] = '\0';
        x /= 2;

        int p = 0;
        for (; p < 256; p ++) if (strcmp(dict[p], str) == 0){
            putc (p, decoded_file);
            t = 0;
        }
    }
    fclose(archive);
    fclose(decoded_file);
    remove(input_file_name);
    rename("tmp.tmp", input_file_name);
    return;
}

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

unsigned char get_char(unsigned int x){
    return ' ' + (x - 32);
}

struct ArchiveFile{
    struct array_uint bytes;
    char* name;
};

void write_file(struct ArchiveFile f){
    FILE* file_out = fopen(f.name, "a");
    fclose(file_out);
    file_out = fopen(f.name, "wb");

    for (int i = 0; i < f.bytes.size; i ++){
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
    FILE* file_out = fopen(archive_name, "ab");

    int name_len = strlen(f.name);
    struct array_uint name_len_4bytes = get_4bytes(name_len);

    for (int i = 0; i < 4; i ++){
        fputc(get_char(get(i, &name_len_4bytes)), file_out);
    }

    printf("name len - %d\n", name_len);
    printf("name len bytes - %u %u %u %u\n", get(0, &name_len_4bytes), get(1, &name_len_4bytes), get(2, &name_len_4bytes), get(3, &name_len_4bytes));

    for (int i = 0; i < name_len; i ++){
        fprintf(file_out, "%c", *(f.name + i));
    }

    struct array_uint data_len_4bytes = get_4bytes(f.bytes.size);

    for (int i = 0; i < 4; i ++){
        fputc(get_char(get(i, &data_len_4bytes)), file_out);
    }

    for (int i = 0; i < f.bytes.size; i ++){
        fputc(get_char(get(i, &f.bytes)), file_out);
    }

    fclose(file_out);
}

int archive_reading_index = 0;

struct ArchiveFile get_file_from_archive(char* archive_name){
    struct array_uint all_bytes = get_file_as_array(archive_name);

    struct array_uint name_len_4bytes = new_array();
    name_len_4bytes = reserve(4);
    for (int j = 0; j < 4; j ++){
        set(j, get(archive_reading_index, &all_bytes), &name_len_4bytes);
        archive_reading_index ++;
    }

    int name_len = get_from_4bytes(&name_len_4bytes);
    char* name = (char*)malloc((name_len + 1)*sizeof(char));
    *(name + name_len) = '\0';

    for (int j = 0; j < name_len; j ++){
        *(name + j) = get_char(get(archive_reading_index, &all_bytes));
        archive_reading_index ++;
    }

    struct array_uint bytes_len_4bytes = new_array();
    bytes_len_4bytes = reserve(4);
    for (int j = 0; j < 4; j ++){
        set(j, get(archive_reading_index, &all_bytes), &bytes_len_4bytes);
        archive_reading_index ++;
    }

    int bytes_len = get_from_4bytes(&bytes_len_4bytes);

    struct array_uint bytes = new_array();
    bytes = reserve(bytes_len);

    for (int j = 0; j < bytes_len; j ++){
        set(j, get(archive_reading_index, &all_bytes), &bytes);
        archive_reading_index ++;
    }

    struct ArchiveFile res;
    res.bytes = bytes;
    res.name = name;
    return res;
}

void extract(char* archive_name){
    struct array_uint data = get_file_as_array(archive_name);
    int i = 0;
    while (archive_reading_index < data.size){
        struct ArchiveFile f = get_file_from_archive(archive_name);
        write_file(f);
        decode(f.name);
        i ++;
    }
}

void add(char* file_name, char* archive_name){
    struct ArchiveFile f = get_file(file_name);
    write_file_in_archive(f, archive_name);
}

void list(char* archive_name){
    struct array_uint data = get_file_as_array(archive_name);
    int i = 0;
    while (archive_reading_index < data.size){
        struct ArchiveFile f = get_file_from_archive(archive_name);
        printf("%s\n", f.name);
        i ++;
    }
    printf("%d\n", i);
}


int main(int argc, char** argv){
    printf("Archivator 2000 start work\n");
    char* archive_name;
    for (int i = 0; i < argc; i ++){
        if (strcmp(argv[i], "--file") == 0){
            archive_name = argv[i + 1];
            i ++;

            continue;
        }
        if (strcmp(argv[i], "--create") == 0){
            remove(archive_name);

            int j = i + 1;
            while (j < argc){
                compress(argv[j]);
                add(argv[j], archive_name);
                decode(argv[j]);
                j ++;
            }
            i = j;

//            compress(archive_name);

            continue;
        }

        if (strcmp(argv[i], "--extract") == 0){
            extract(archive_name);
//            compress(archive_name);
        }

        if (strcmp(argv[i], "--list") == 0){
//            decode(archive_name);
            list(archive_name);
//            compress(archive_name);
        }

        if (strcmp(argv[i], "--size") == 0){
            printf("%d\n", fseek_filesize(archive_name));
        }

        if (strcmp(argv[i], "--bytes") == 0){
            struct array_uint res = get_file_as_array(archive_name);
            for (int i = 0; i < res.size; i ++){
                printf("%u\n", get(i, &res));
            }

            printf("%u -- first byte\n %u -- last byte\n", get(0, &res), get(res.size - 1, &res));
        }
    }
}
