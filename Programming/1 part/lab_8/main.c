#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    //1 4 5 7 10
    char str1[100], str2[100];
    gets(str1);
    gets(str2);

    char str3[100];
    strcpy(str3, str1);

    strcat(str3, str2);



    printf("%s %s %s\n", str3, str1, str2);

    // -----------

    int n;
    scanf("%d", &n);

    int status = 0;

    for (int i = 0; i < n; i ++){
        if ((int)str1[i] != (int)str2[i])
        {
            if ((int)str1[i] < (int)str2[i]){
                status  = -1;
            }
            else {
                status = 1;
            }
        }
    }

    printf("%d\n", status);

    //------------------------

    char str[100], str_copy[100];
    scanf("%s", str);
    strcpy(str_copy, str);
    printf("%s\n", str_copy);


    //------------------------

    printf("%d\n", strlen(str));

    //-------------------------

    int place = -1;

    for (int i = 0; i < strlen(str1); i ++){
        for (int j = 0; j < strlen(str2); j ++){
            if ((int)str1[i] == (int)str2[j]){
            place = i;
            break;
        }
    }

    printf("%d", place);

}
