#ifndef LAB14_BMP_H
#define LAB14_BMP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dir.h>

int numLen(int a) {
    int res = 0;
    if (a < 0) a = -a;
    while (a > 0) {
        a /= 10;
        res ++;
    }
    return res;
}

char *makePath(char *directory, int order, char *extension) {
    int size = numLen(order);
    int dir_size = (int) strlen(directory);

    char *name = malloc(size + 1);
    sprintf(name, "%d", order);
    name[size] = '\0';

    char *path = calloc(dir_size + strlen(name) + strlen(extension), sizeof(char));
    strcpy(path, directory);
    strcat(path, name);
    strcat(path, extension);

    free(name);
    return path;
}

void num_in_16th(FILE *f, int a, int size) {
    if (a < 0) a = -a;
    for (int i = 0; i < size; i ++) {
        fputc(a % 256, f);
        a /= 256;
    }
}

void inverseArray(int **array, int height){
    for (int i = 0; i < height / 2; i ++) {
        int* tmp = array[i];
        array[i] = array[height - i - 1];
        array[height - i - 1] = tmp;
    }
}

void putcolor(FILE *f, int a) {
    for (int i = 0; i < 2; i ++) fputc(a % 256, f);
}

void getcolor(FILE *f, int *a) {
    int k1 = fgetc(f);
    int k2 = fgetc(f);
    *a = fgetc(f);
}

void num_from_16th(FILE *f, int *a) {
    *a = 0;
    int pw256 = 1;
    for (int i = 0; i < 4; i ++){
        *a += fgetc(f);
        pw256 *= 256;
    }
}

void three_put(int a, FILE* f){
    for (int i = 0;  i < 3; i ++) fputc(a, f);
}

void two_put(int a, FILE* f){
    for (int i = 0; i < 2; i ++) fputc(a, f);
}

void k_put(int a, FILE* f, int k){
    for (int i = 0; i < k; i ++) fputc(a, f);
}

void write_headers(FILE* f){
    int k = 4;
    int headers[3] = {0, 54, 40};
    for (int i = 0; i < 3; i ++) num_in_16th(f, headers[i], k);
}

void write_headers_2(FILE* f){
    int headers[2] = {24, 0};
    for (int i = 0; i < 2; i ++) fputc(headers[i], f);
}

void saveBMP(int **array, int height, int width, char *fileName) {
    FILE *f = fopen(fileName, "wb");

    fputc('B', f);
    fputc('M', f);

    int offset = offset = 4 - ((width * 3) % 4);
    offset = offset % 4;

    num_in_16th(f, 56 + (int) (sizeof(int) * height * width + sizeof(int) * height * offset), 4);

    write_headers(f);
    int k = 4;
    num_in_16th(f, width, k);
    num_in_16th(f, height, k);
    for (int i = 1; i >= 0; i --) fputc(i, f);
    write_headers_2(f);

    num_in_16th(f, 0, 4);
    num_in_16th(f, width * height, 4);

    for (int i = 0; i < 2; i ++) {
        fputc(195, f);
        fputc(14, f);
        k_put(0, f, 2);
    }

    for (int i = 0; i < 2; i ++){
        fputc(2, f);
        three_put(0, f);
    }

    inverseArray(array, height);

    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j ++) putcolor(f, array[i][j]);
        for (int k = 0; k < offset; k ++) fputc(0, f);
    }

    fclose(f);
}

void reserve_memory(int** arr, int width, int height){
    arr = calloc(height, sizeof(int*));
    for (int i = 0; i < height; i ++) arr[i] = calloc(width, sizeof(int));
}

int **openBMP(int *height, int *width, char *inputFileName) {
    FILE *f = fopen(inputFileName, "rb");
    fseek(f, 18, SEEK_SET);
    num_from_16th(f, width);
    num_from_16th(f, height);
    int **array;
    reserve_memory(array, (*width), (*height));
    int offset = 4 - ((*width * 3) % 4);
    offset = offset % 4;
    fseek(f, 54, SEEK_SET);
    for (int i = 0; i < (*height); i ++) {
        for (int j = 0; j < (*width); j ++) getcolor(f, &array[i][j]);
        for (int k = 0; k < offset; k ++) fgetc(f);
    }
    inverseArray(array, (*height));
    return array;
};

#endif
