#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    FILE* archive = fopen(input_file_name, "rb");
    FILE* decoded_file = fopen("tmp.tmp", "wb");
    unsigned char** dict = (unsigned char**)malloc(256 * sizeof(unsigned char*));
    for (int i = 0; i < 256; i ++)
        dict[i] = (unsigned char*)malloc(256 + sizeof(char));
    int n = fgetc(archive);
    n ++;
    for (int i = 0; i < n; i ++){
        int x = getc(archive);
        int y = getc(archive);
        for (int j = 0; j < y / 8; ++ j){
            int a = getc (archive);
            write_num_to_str(a, dict[x], 8 * j, 8);
        }
        if (y % 8 != 0){
            int a = getc (archive);
            write_num_to_str(a, dict[x], y / 8 * 8, y % 8);
        }
    }
    unsigned char* str = (unsigned char*)calloc(256, sizeof(char));
    int buff[2], t = 0;
    int c = getc(archive);
    buff[1] = c;
    c = fgetc(archive);
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

#define debug_mode_2

int main(void){
    char* file_name = "in/1.bmp";
    #ifdef debug_mode_1
    compress(file_name);
    #endif
    #ifdef debug_mode_2
    decode(file_name);
    #endif
    #ifdef debug_mode_3
        compress(file_name);
        decode(file_name);
    #endif // debug_mode_3
}
