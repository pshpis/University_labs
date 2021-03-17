#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

char *inputFile = 0;
char *outputDirectory = 0;
int maxIteration = -1;
int frequency = 1;

typedef struct {
    int height;
    int width;

    int **current;

    int count;
    int ***generations;
} BOARD;

BOARD *newBoard(int height, int width, int **array) { //создание доски
    BOARD *board = malloc(sizeof(BOARD));

    board->height = height;
    board->width = width;

    board->current = array;

    board->count = 0;
    board->generations = calloc(0, sizeof(int **));

    return board;
}

int neighbours(int **array, int i, int j, int height, int width){ //сумма всех соседей
    int a = 0;

    a += array[(i + 1 + height) % height][(j - 1 + width) % width] == 0;
    a += array[(i + 1 + height) % height][(j + width) % width] == 0;
    a += array[(i + 1 + height) % height][(j + 1 + width) % width] == 0;

    a += array[(i + height) % height][(j - 1 + width) % width] == 0;
    a += array[(i + height) % height][(j + 1 + width) % width] == 0;

    a += array[(i - 1 + height) % height][(j - 1 + width) % width] == 0;
    a += array[(i - 1 + height) % height][(j + width) % width] == 0;
    a += array[(i - 1 + height) % height][(j + 1 + width) % width] == 0;

    return a;
}

int compareGenerations(BOARD *board){ // проверка на то что текущая итерация уникальна
    for (int c = 0; c < board -> count; c ++) {
        int a = 0;
        for (int i = 0; i < board->height; i ++) {
            for (int j = 0; j < board->width; j ++) {
                if (board->generations[c][i][j] == board->current[i][j])
                    a++;
            }
        }
        if (a == board->height * board->width)
            return 1;
    }

    return 0;
}

void archive(BOARD *board) {//выделение памяти
    board->generations = realloc(board->generations, sizeof(int **) * (board->count + 1));

    board->generations[board->count++] = board->current;

    board->current = calloc(board->height, sizeof(int *));
    for (int i = 0; i < board->height; i ++) {
        board->current[i] = calloc(board->width, sizeof(int));
    }
}

int cycle(BOARD *board) { // построение новой генерации
    archive(board);

    int alive = 0;

    int **last = board->generations[board->count - 1];

    for (int i = 0; i < board->height; i ++) {
        for (int j = 0; j < board->width; j ++) {
            int n = neighbours(last, i, j, board->height, board->width);

            if (last[i][j] == 255 && n == 3) {
                board->current[i][j] = 0;
                alive++;
            } else if (last[i][j] == 255)
                board->current[i][j] = 255;

            if (last[i][j] == 0 && (n < 2 || n > 3))
                board->current[i][j] = 255;
            else if (last[i][j] == 0) {
                board->current[i][j] = 0;
                alive++;
            }
        }
    }

    return alive && compareGenerations(board);
}

void play(BOARD *board){
    int result = cycle(board);
    int cycles = 1;

    char *fileName = makePath(outputDirectory, cycles, ".bmp\0");

    if (cycles % frequency == 0) {
        saveBMP(board->generations[board->count - 1],
                board->height,
                board->width,
                fileName);
    }

    while (result == 0 && (maxIteration == -1 || cycles < maxIteration)){
        result = cycle(board);
        cycles ++;

        if (cycles % frequency == 0) {
            free(fileName);
            fileName = makePath(outputDirectory, cycles, ".bmp\0");

            saveBMP(board->generations[board->count - 1],
                    board->height,
                    board->width,
                    fileName);
        }
    }

    free(fileName);
}


int main(int argc, char **argv) {

#define debug

#ifdef debug
    argc = 9;
    argv[1] = "--input";
    argv[2] = "glider.bmp";
    argv[3] = "--output";
    argv[4] = "a/";
    argv[5] = "--max_iter";
    argv[6] = "30";
    argv[7] = "--dump_freq";
    argv[8] = "5";
#endif

    for (int i = 1; i < argc; i++) {
        if (strcmp("--input", argv[i]) == 0) {
            int len = strlen(argv[i + 1]);
            if (!(argv[i + 1][len - 4] == '.' && argv[i + 1][len - 3] == 'b' && argv[i + 1][len - 2] == 'm' &&
                  argv[i + 1][len - 1] == 'p')) {
                printf("\nWrong input file format\n");
                exit(0);
            }

            inputFile = malloc(strlen(argv[i + 1]) + 1);
            strcpy(inputFile, argv[i + 1]);
            inputFile[strlen(argv[i + 1])] = '\0';
        } else if (strcmp("--output", argv[i]) == 0) {
            outputDirectory = malloc(strlen(argv[i + 1]) + 1);
            strcpy(outputDirectory, argv[i + 1]);
            outputDirectory[strlen(argv[i + 1])] = '\0';

            mkdir(outputDirectory);
        } else if (strcmp("--max_iter", argv[i]) == 0) {
            maxIteration = atoi(argv[i + 1]);
        } else if (strcmp("--dump_freq", argv[i]) == 0) {
            frequency = atoi(argv[i + 1]);
        }
    }

    if (inputFile && outputDirectory) {
        int height, width;

        int **array = openBMP(&height, &width, inputFile);

        BOARD *board = newBoard(height, width, array);

        play(board);
    }

    return 0;
}
