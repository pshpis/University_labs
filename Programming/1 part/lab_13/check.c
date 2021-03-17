#include <stdio.h>
#include <string.h>
int a = 3;

int cmp(char* str1, char* str2){
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int i;
    for (i = 0; i < min(len1, len2); i ++){
        if (str1[i] > str2[i]) return 1;
        if (str1[i] < str2[i]) return -1;
    }

    if (len1 == len2) return 0;
    if (len1 < len2) return 1;
    return -1;
}

int main(void){

}
