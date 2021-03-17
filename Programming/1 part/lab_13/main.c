#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define int long long

char* read_tag(FILE* song){
    char* tag = malloc(10);
    fread(tag, 1, 10, song);
    return tag;
}

void write_standard(FILE* song){
    char* tag = read_tag(song);

    printf("%s", tag); //standard name
    printf("%d.%d%d\n", *(tag + 3), *(tag + 4), *(tag + 5)); // version
    free(tag);
}

int get_binary_num(char* str, int l, int r){
    int res = 0;
    int pw256 = 1;
    if (l > r)
        for (int i = l; i >= r; i --){
            res += *(str + i) * pw256;
            pw256 *= 256;
        }
    else
        for (int i = l; i <= r; i ++){
            res += *(str + i) * pw256;
            pw256 *= 256;
        }
    return res;
}

void write_bin

void show(char* song_name, char* field_name){
    FILE* song = fopen(song_name, "rb");
    if (strcmp(field_name, "all_fields") == 0) write_standard(song);
    else fseek(song, 10, SEEK_SET);

    char* tag;

    while (true){
        tag = read_tag(song);

        int tag_info_size = get_binary_num(tag, 7, 4);

        char* tag_name = malloc(5);
        for (int i = 0; i < 4; i ++) *(tag_name + i) = *(tag + i);
        *(tag_name + 4) = '\0';

        if (tag_info_size == 0 || strcmp(tag_name, "0000") == 0) break;

        if (strcmp(field_name, "all_fields") == 0 || strcmp(tag_name, field_name) == 0){
            char *tag_value = malloc(tag_info_size);
            printf("%s ", tag);

            printf("%d %d ", tag[8], tag[9]);

            fread(tag_value, 1, tag_info_size, song);

            for (int i = 0; i < tag_info_size; i ++) printf("%c", *(tag_value + i));
            printf("\n");

            free(tag_value);
            if (strcmp(field_name, "all_fields") != 0) break;
        }
        else {
            fseek(song, tag_info_size, SEEK_CUR);
        }
    }


    free(tag);
    fclose(song);
}

void set(char *song_name, char *field_name, char *value){
    char *tag = malloc(10);
    FILE *song = fopen(song_name, "rb");
    FILE *buffer_song = fopen("_______________________buffer.mp3", "wb"); // что не хранить все в оперативке
    fread(tag, 1, 10, song);
    fwrite(tag, 1, 10, buffer_song);

    int info_size = get_binary_num(tag, 9, 6);
    int old_tag_info_size = 0;
    int new_tag_info_size = (int) strlen(value);

    while (ftell(song) < info_size + 10){
        fread(tag, 1, 10, song);
        char* tag_name = malloc(5);
        tag_name[0] = tag[0];
        tag_name[1] = tag[1];
        tag_name[2] = tag[2];
        tag_name[3] = tag[3];
        tag_name[4] = '\0';

        int tag_info_size = get_binary_num(tag, 7, 4);

        if (tag_info_size == 0 || strcmp(tag_name, "0000") == 0) break;

        if (strcmp(tag_name, field_name) != 0){
            fwrite(tag, 1, 10, buffer_song);
            int c;
            for (int i = 0; i < tag_info_size; i++){
                c = getc(song);
                putc(c, buffer_song);
            }
        }
        else{
            *(tag + 7) = (char) (new_tag_info_size % 256);
            *(tag + 6) = (char) (new_tag_info_size / 256 % 256);
            *(tag + 5) = (char) (new_tag_info_size / 256 / 256 % 256);
            *(tag + 4) = (char) (new_tag_info_size / 256 / 256 / 256 % 256);

            old_tag_info_size = tag_info_size;

            for (int i = 0; i < 10; i ++) putc(tag[i], buffer_song);
            for (int i = 0; i < new_tag_info_size; i ++) putc(value[i], buffer_song);
            fseek(song, tag_info_size, SEEK_CUR);
            break;
        }
    }

    int cur = ftell(song);
    fseek(song, 0, SEEK_END);
    int end = ftell(song);
    fseek(song, cur - end, SEEK_END);

    char *song_data = malloc((end - cur) + 1);
    fread(song_data, 1, end - cur, song);
    song_data[end - cur] = '\0';
    fwrite(song_data, 1, end - cur, buffer_song);

    free(song_data);

    fseek(song, 0, SEEK_SET);
    fseek(buffer_song, 0, SEEK_SET);

    fread(tag, 1, 10, song);

    info_size += new_tag_info_size - old_tag_info_size;
    *(tag + 9) = (char) (info_size % 256);
    *(tag + 8) = (char) (info_size / 256 % 256);
    *(tag + 7) = (char) (info_size / 256 / 256 % 256);
    *(tag + 6) = (char) (info_size / 256 / 256 / 256 % 256);

    for (int i = 0; i < 10; i++) putc(tag[i], buffer_song);

    fclose(song);
    fclose(buffer_song);
    remove(song_name);
    rename("_______________________buffer.mp3", song_name);

    free(tag);
}

unsigned main(int argc, char** argv){
    int song_name_size = strlen(argv[1]) - strlen("--filepath=");
    char *song_name = malloc(song_name_size + 1);

    for (int i = strlen("--filepath="); i < strlen("--filepath=") + song_name_size; i ++)
        *(song_name + i - strlen("--filepath=")) = argv[1][i];
    song_name[song_name_size] = '\0';

    if (strcmp(argv[2], "--show") == 0) show(song_name, "all_fields");
    else if (argv[2][2] == 'g'){
        char* tag_name = malloc(5);
        tag_name[0] = argv[2][6];
        tag_name[1] = argv[2][7];
        tag_name[2] = argv[2][8];
        tag_name[3] = argv[2][9];
        tag_name[4] = '\0';
        show(song_name, tag_name);
        free(tag_name);
    }
    else {
        int value_size = (int) strlen(argv[3]) - strlen("--value=");

        char* tag_name = malloc(5);
        tag_name[0] = argv[2][6];
        tag_name[1] = argv[2][7];
        tag_name[2] = argv[2][8];
        tag_name[3] = argv[2][9];
        tag_name[4] = '\0';

        char *value = malloc(value_size + 1);
        for (int i = strlen("--value="); i < strlen("--value=") + value_size; i++) value[i - strlen("--value=")] = argv[3][i];
        value[value_size] = '\0';

        set(song_name, tag_name, value);
        free(value);
        free(tag_name);
    }

}
