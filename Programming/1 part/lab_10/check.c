#include <stdio.h>
#include <stdlib.h>

void mult(int n, int *arr1, int *arr2, int *res){
    for (int line = 0; line < n; line++){
        for (int column = 0; column < n; column++){
            *(res+ n*line + column) = 0;
            for (int offset = 0; offset < n; offset ++){
                *(res+ n*line + column) += *(arr1+ offset*n + column)* *(arr2 + line*n + offset);
            }
        }
    }
}

int main(void){
    int a[] = {90, 76, 54, 23, 56, 12, 48};
    for (int i = 0; i < 7; i ++) printf("%d ", a[i]);

    int arr1[2][2] = {1, 2,3, 1};
    int arr2[2][2] = {1, 1, 0, 2};

    int sizeOfInt = sizeof(int);
    int a1l = 2, a1c = 2, *array1 = malloc(a1l*a1c*sizeOfInt);
    int a2l = 2, a2c = 2, *array2 = malloc(a1l*a1c*sizeOfInt);
    int rl = 2, rc = 2, *result = malloc(rl*rc*sizeOfInt);

    for (int line = 0; line < a1l; line++)
    {
        for (int column = 0; column < a1c; column++)
        {
            *(array1+ line*a1c + column) = arr1[line][column];
        }
    }

    for (int line = 0; line < a2l; line++)
    {
        for (int column = 0; column < a2c; column++)
        {
            *(array2+ line*a2c + column) = arr2[line][column];
        }
    }

    mult(2, array1, array1, result);

    for (int line = 0; line < 2; line++){
        for (int column = 0; column < 2; column++){
            printf("%d ", *(result+ rl*line + column));
        }
    }



}
