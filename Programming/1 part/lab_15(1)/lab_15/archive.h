#include <stdio.h>
#include <string.h>

#include "files_func.h"
#include "array_int.h"
#include "4bytes_int_func.h"

#ifndef archive_was_declarated
#define archive_was_declarated

unsigned char get_char(int x){
    return ' ' + (x - 32);
}

struct ArchiveFile{
    struct array_int bytes;
    char* name;
};

void write_file(struct ArchiveFile f){
    FILE* file_out = fopen(f.name, "a");
    fclose(file_out);
    file_out = fopen(f.name, "w");

    for (int i = 0; i < f.bytes.size; i ++){
        fputc(get(i, &f.bytes), file_out);
    }

    fclose(file_out);

    return;
}

struct ArchiveFile get_file(char* file_name){
    struct ArchiveFile res;
    res.name = file_name;
    res.bytes = get_file_as_array(file_name);
    return res;
}

void write_file_in_archive(struct ArchiveFile f, char* archive_name){
    FILE* file_out = fopen(archive_name, "a");

    int name_len = strlen(f.name);
    struct array_int name_len_4bytes = get_4bytes(name_len);

    for (int i = 0; i < 4; i ++){
        fputc(get_char(get(i, &name_len_4bytes)), file_out);
    }

    for (int i = 0; i < name_len; i ++){
        fprintf(file_out, "%c", *(f.name + i));
    }

    struct array_int data_len_4bytes = get_4bytes(f.bytes.size);

    for (int i = 0; i < 4; i ++){
        fputc(get_char(get(i, &data_len_4bytes)), file_out);
    }

    for (int i = 0; i < f.bytes.size; i ++){
        fputc(get_char(get(i, &f.bytes)), file_out);
    }

    fclose(file_out);
}

int archive_reading_index = 0;

struct ArchiveFile get_file_from_archive(char* archive_name){
    struct array_int all_bytes = get_file_as_array(archive_name);

    struct array_int name_len_4bytes = new_array();
    name_len_4bytes = reserve(4);
    for (int j = 0; j < 4; j ++){
        set(j, get(archive_reading_index, &all_bytes), &name_len_4bytes);
        archive_reading_index ++;
    }

    int name_len = get_from_4bytes(&name_len_4bytes);
    char* name = (char*)malloc((name_len + 1)*sizeof(char));
    *(name + name_len) = '\0';

    for (int j = 0; j < name_len; j ++){
        *(name + j) = get_char(get(archive_reading_index, &all_bytes));
        archive_reading_index ++;
    }

    struct array_int bytes_len_4bytes = new_array();
    bytes_len_4bytes = reserve(4);
    for (int j = 0; j < 4; j ++){
        set(j, get(archive_reading_index, &all_bytes), &bytes_len_4bytes);
        archive_reading_index ++;
    }

    int bytes_len = get_from_4bytes(&bytes_len_4bytes);

    struct array_int bytes = new_array();
    bytes = reserve(bytes_len);

    for (int j = 0; j < bytes_len; j ++){
        set(j, get(archive_reading_index, &all_bytes), &bytes);
        archive_reading_index ++;
    }

    struct ArchiveFile res;
    res.bytes = bytes;
    res.name = name;
    return res;
}

void extract(char* archive_name){
    struct array_int data = get_file_as_array(archive_name);
    int i = 0;
    while (archive_reading_index < data.size){
        struct ArchiveFile f = get_file_from_archive(archive_name);
        write_file(f);
        i ++;
    }
}

void add(char* file_name, char* archive_name){
    struct ArchiveFile f = get_file(file_name);
    write_file_in_archive(f, archive_name);
}

void list(char* archive_name){
    struct array_int data = get_file_as_array(archive_name);
    int i = 0;
    while (archive_reading_index < data.size){
        struct ArchiveFile f = get_file_from_archive(archive_name);
        printf("%s\n", f.name);
        i ++;
    }
    printf("%d\n", i);
}

#endif
