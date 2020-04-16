#pragma once

#include <config.h>

wchar_t* join_path(wchar_t* dir1, wchar_t* dir2);
wchar_t* copy_string(wchar_t* string);
wchar_t* convert_string(char* string);
void normalize_string(wchar_t* string);
void denormalize_string(wchar_t* string);
uint32_t read_uint32_t(FILE* file);
wchar_t *_wstrrchr(register const  wchar_t*s, wchar_t c);
int is_dir(wchar_t *path);
char* w2c(wchar_t* string);
int isDirectoryEmpty(wchar_t *dirname);
int LoadToArray(wchar_t* file, char** data, uint32_t* size);