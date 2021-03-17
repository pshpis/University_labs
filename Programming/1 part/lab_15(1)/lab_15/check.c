#include <stdio.h>

#include "archive.h"

int main(int argc, char** argv){
    printf("Archivator 2000 start work\n");
    char* archive_name;
    for (int i = 0; i < argc; i ++){
        if (strcmp(argv[i], "--file") == 0){
            archive_name = argv[i + 1];
            i ++;

            continue;
        }
        if (strcmp(argv[i], "--create") == 0){
            FILE* tmp = fopen(archive_name, "a");
            fclose(tmp);
            tmp = fopen(archive_name, "w");
            fclose(tmp);

            int j = i + 1;
            while (j < argc){
                add(argv[j], archive_name);
                j ++;
            }
            i = j;
            continue;
        }
        if (strcmp(argv[i], "--extract") == 0){
            extract(archive_name);
        }
        if (strcmp(argv[i], "--list") == 0){
            list(archive_name);
        }
    }
//
//    for (int i = 0; i < argc; i ++){
//        printf("%s\n", argv[i]);
//    }
//
//    printf("%d", strcmp(argv[1], "--file"));

}
