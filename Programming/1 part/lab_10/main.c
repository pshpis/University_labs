#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int sum_nums(int n){
    if (n / 10 == 0) return n % 10;
    return (n % 10) + sum_nums(n / 10);
}

struct Point{
    int x;
    int y;
};

double dist(struct Point a, struct Point b){
//    printf("I am in func dist");
    return sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
}

double* get_dist(struct Point *arr, int n){
    double *distanse = malloc(n * (n) * sizeof(double));
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            if (i != j){
                int j_ = j;
                *(distanse + (i * (n - 1)) + j_) = dist(arr[i], arr[j_]);
            }
        }
    }
    return distanse;
}

int main(void){
    int n;
    scanf("%d", &n);


    struct Point *arr = malloc(n * sizeof(struct Point));

    for (int i = 0; i < n; i ++){
        int x, y;
        scanf("%d%d", &x, &y);
        struct Point p;
        p.x = x;
        p.y = y;

        arr[i] = p;
    }

    double* dist = get_dist(arr, n);

    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            if (i != j){
                printf("%lf \n", *(dist + (i * (n - 1)) + j));
            }
        }
    }



    /*
3
1 2
1 3
1 4
    */


    int num;
    scanf("%d", &num);
    printf("%d", sum_nums(num));
}
