#include <stdio.h>
#include <math.h>

int main (void)
{
    int a;
    scanf("%x", &a); // 1st task
    printf("%d\n", a); // 2nd task
    printf("%x  %x\n", a, a >> 2); //3rd task
    printf("%x  %x\n", a, ~a); //4th task

    int b;
    scanf("%x", &b);
    printf("%x\n", a | b); //5th task
}

