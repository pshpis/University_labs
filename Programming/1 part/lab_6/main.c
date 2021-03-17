#include <stdio.h>
#include <stdlib.h>

int main(void){
    printf("---FIRST TASK---\n");
    int a[4];

    printf("WRITE 4 NUMBERS\n");
    for (int i = 0; i < 4; i ++){
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < 4; i ++){
        printf("%d ", *(a + i));
    }
    printf("\n---SECOND TASK---\n");

    int *b;
    b = (int*)malloc(4 * sizeof(int));

    printf("WRITE 4 NUMBERS\n");
    for (int i = 0; i < 4; i ++){
        scanf("%d", &b[i]);
    }

    for (int i = 0; i < 4; i ++){
        printf("%d ", *(b + i));
    }

    free(b);

    return 0;
}
