#define min(x, y) x < y ? x : y
#define max(x, y) x > y ? x : y

#ifndef shenon_fano_was_declarated
#define shenon_fano_was_declarated

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files_func.h"
#include "array_int.h"
#include "pair.h"

char** shenon_fano_codes;

void SearchTree (int *symbols, int *freq, char* branch, char* fullBranch, int start, int end){
    if (freq[start] == 0) return;
    double dS = 0;
    int i, m, S = 0;
    char* cBranch = "";

    cBranch = concat(fullBranch, branch);
    if (start == end){
        printf("%d ---- %s\n", symbols[start], cBranch);
        shenon_fano_codes[start] = cBranch;
        return;
    }

    for (i = start; i <= end; i ++) dS += freq[i];

    dS /= 2.;
    i = start + 1;
    S += freq[start];
    while (fabs(dS - (S + freq[i])) < fabs(dS - S) && (i < end) && (freq[i] > 0)){
        S += freq[i];
        i ++;
    }

    char* zero = "0";
    char* one = "1";
    SearchTree(symbols, freq, one, cBranch, start, i - 1);
    SearchTree(symbols, freq, zero, cBranch, i, end);
}

int shenon_fano(char* file_name){
    struct array_uint bytes = get_file_as_array(file_name);
    struct pair* frequency = malloc(256 * sizeof(struct pair));
    for (int i = 0; i < 256; i ++){
        frequency[i] = new_pair(0, i);
    }

    for (int i = 0; i < bytes.size; i ++){
        unsigned int byte = get(i, &bytes);
        unsigned int fr = frequency[byte].first;
        frequency[byte] = new_pair(fr + 1, byte);
    }

    qsort(frequency, 256, sizeof(struct pair), pair_cmp);

    int* symbols = malloc(256 * sizeof(int));
    int* freq = malloc(256 * sizeof(int));

    for (int i = 255; i >= 0; i --){
        symbols[255 - i] = frequency[i].second;
        freq[255 - i] = frequency[i].first;
    }

    for (int i = 0; i < 256; i ++){
        printf("%d - %d\n", symbols[i], freq[i]);
    }

    char* branch = "";
    char* fullBranch = "";
    shenon_fano_codes = malloc(256 * sizeof(char*));

    SearchTree(symbols, freq, branch, fullBranch, 0, 255);

    int sum = 0;
    for (int i = 0; i < bytes.size; i ++){
        for (int i = 0; i < 256; i ++){
            if (symbols[i] == get(i, &bytes)){
                sum += strlen(shenon_fano_codes[i]);
            }
        }
    }

    printf("\nAAAAAAAAAAAAAAAAA\n%d\n", sum);
}

#endif
