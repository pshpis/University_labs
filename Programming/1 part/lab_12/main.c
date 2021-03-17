#include <stdio.h>

int main(int argc, char **argv){
//    printf(argv[1]);
    FILE* file_in = fopen(argv[1], "r");
    if (file_in == NULL){
        return -1;
    }
    int i = 0;
    while (1)
   {
      char str[50];
      char *estr = fgets (str, file_in);

      if (estr == NULL)
      {
         break;
      }

      if (i % 2 == 1) printf ("%s \n",str);

      i ++;
   }
   return 0;
}
