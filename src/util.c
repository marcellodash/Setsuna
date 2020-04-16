#include <util.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

wchar_t* join_path(wchar_t* dir1, wchar_t* dir2) {
	int dir1_size = wcslen(dir1) * sizeof(wchar_t);
	int dir2_size = wcslen(dir2) * sizeof(wchar_t);
	int bar_and_null_size = 2 * sizeof(wchar_t);
	int new_dir_size = dir1_size + dir2_size + bar_and_null_size;
	wchar_t* new_dir = malloc(new_dir_size);
	memset(new_dir, 0, new_dir_size);
	if (wcscat_s(new_dir, new_dir_size, dir1) == 0) {
		if (wcscat_s(new_dir, new_dir_size, L"\\") == 0) {
			if (wcscat_s(new_dir, new_dir_size, dir2) == 0) {
				return new_dir;
			}
		}
	}

	return NULL;
}

wchar_t* copy_string(wchar_t* string) {
	int string_size = (wcslen(string) + 1) * sizeof(wchar_t);
	wchar_t* new_string = malloc(string_size);
	memset(new_string, 0, string_size);
	wcscat_s(new_string, string_size, string);
	return new_string;
}

wchar_t* convert_string(char* string) {
	int new_string_size = (strlen(string) + 1) * sizeof(wchar_t);
	wchar_t* new_string = malloc(new_string_size);
	memset(new_string, 0, new_string_size);
	mbstowcs(new_string, string, new_string_size);
	return new_string;
}

char* w2c(wchar_t* string) {
	int new_string_size = (wcslen(string) + 2) * sizeof(char);
	char* new_string = malloc(new_string_size);
	memset(new_string, 0, new_string_size);
	wcstombs(new_string, string, new_string_size);
	return new_string;
}

void normalize_string(wchar_t* string) {
	while (string[0] != L'\0') {
		if (string[0] == L'?') {
			string[0] = L';';
		}
		string++;
	}
}

void denormalize_string(wchar_t* string) {
	while (string[0] != L'\0') {
		if (string[0] == L';') {
			string[0] = L'?';
		}
		string++;
	}
}

uint32_t read_uint32_t(FILE* file) {
	uint32_t out;
	fread(&out, 4, 1, file);
	return out;
}

wchar_t *_wstrrchr(register const  wchar_t*s, wchar_t c) {
	register const wchar_t *p;

	p = NULL;
	do {

		if (*s == c) {
			p = s;
		}
	} while (*s++);

	return (wchar_t *) p;
}

int is_dir(wchar_t *path) {
	struct _stat32 path_stat;
	_wstat(path, &path_stat);
	return !S_ISREG(path_stat.st_mode);
}


int isDirectoryEmpty(wchar_t *dirname) {
	int n = 0;
	struct _wdirent *d;
	_WDIR *dir = _wopendir(dirname);
	if (dir == NULL)
		return 1;
	while ((d = _wreaddir(dir)) != NULL) {
		if (++n > 2)
			break;
	}
	_wclosedir(dir);
	if (n <= 2)
		return 1;
	else
		return 0;
}

int LoadToArray(wchar_t* file, char** data, uint32_t* size) {
	FILE *fileptr;
	char *buffer;
	uint32_t filelen;

	fileptr = _wfopen(file, L"rb");
	fseek(fileptr, 0, SEEK_END);
	filelen = ftell(fileptr);
	rewind(fileptr);
	buffer = (char *)malloc(filelen * sizeof(char));
	fread(buffer, filelen, 1, fileptr);
	*data = buffer;
	*size = filelen;
	fclose(fileptr);
	return 0;
}