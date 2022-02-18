#include "data.h"
#include <stdio.h>

const char file_path[50] = "./save_data.txt";
FILE* save_data = NULL;

FILE* open_file_read() {
    return save_data = fopen(file_path, "r");
}

FILE* open_file_write() {
    return save_data = fopen(file_path, "w");
}

void close_file() {
    fclose(save_data);
    save_data = NULL;
}