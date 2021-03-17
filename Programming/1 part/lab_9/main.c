#include <stdio.h>
#include <stdlib.h>

int main(void){
    int call_time, standart_pay, over_pay;

    scanf("%d%d%d", &call_time, &standart_pay, &over_pay);

    int over_time = call_time - 499;
    int pay = standart_pay;
    if (over_time > 0)  pay += over_time * over_pay;

    printf("%d \n -------- \n\n", pay);


    int num;
    scanf("%d", &num);

    int *erotosf = malloc((num + 1)*sizeof(int));

    for (int i = 0; i <= num; i++) {
            erotosf[i] = 1;
    }

    for (int i = 2; i <= num; i++)
    {
        if (erotosf[i] == 1)
        {
            printf("%d ", i);
            for (int j = 2*i; j <= num; j += i){
                    erotosf[j] = 0;
            }
        }
    }

    free(erotosf);

    return 0;

}
