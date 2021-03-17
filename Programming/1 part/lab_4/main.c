#include <stdio.h>
#include <math.h>

int main (void)
{
    int a;
    scanf("%d", &a);

    int more_75 = (a >= 76);
    int less_79 = (a <= 78);

    printf("%d\n", more_75 & less_79);

    int b;
    scanf("%d", &b);
    b = b >> 6;

    printf("%d\n", b % 2);
}


