#include "io.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* read_file(const char* path, int* data_len) {
  FILE* f = fopen(path, "r");
  char* data = 0;
  fseek(f , 0 , SEEK_END);
  *data_len = ftell(f) + 1;
  rewind(f);
  data = (char*) malloc(*data_len);

  fread(data, 1, *data_len, f);
  fclose(f);
  data[*data_len-1] = 0;
  return data;
}

void write_file(const char* path, char* data, int data_len) {
  FILE* f = fopen(path, "w");
  fwrite(data, 1, data_len, f);
  fclose(f);
}

char* get_curr_dir_name() {
  char* final_name = "";
  #define CURR_DIR_BUF_SIZE 1024
  char curr_dir[CURR_DIR_BUF_SIZE];
  #ifdef WIN32
  GetModuleFileName(NULL, &(curr_dir[0]), CURR_DIR_BUF_SIZE);
  // Loop backwards from end of string, strip the exe name
  char* last_char = strrchr(curr_dir, '\\');
  last_char[1] = 0;
  unsigned curr_dir_len = strlen(curr_dir);
  final_name = (char*)malloc(curr_dir_len);
  memcpy(final_name, curr_dir, curr_dir_len);
  #endif
  return final_name;
}
