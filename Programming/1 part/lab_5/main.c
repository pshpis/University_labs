#include <stdio.h>

int main(void){
    int a[] = {90, 76, 54, 23, 56, 12, 48};
    for (int i = 0; i < 7; i ++) printf("%d ", a[i]);

    int arr1[2][2] = {
        {1, 2},
        {3, 1}
    };

    int arr2[2][2] = {
        {1, 1},
        {0, 2}
    };


    int res[2][2];

    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j ++){
            res[i][j] = 0;
            for (int k = 0; k < 2; k ++){
                res[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }


    printf("\n");

    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j ++){
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }



}
