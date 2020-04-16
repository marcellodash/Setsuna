#pragma once
#include <stdint.h>
#include <config.h>
#include <stdbool.h>

#define DIRECTORY_SIGN 3435973836

typedef struct KCAPEntry {
	uint32_t compressed;
	unsigned char* filename;
	uint64_t unknown;
	uint32_t offset;
	uint32_t length;
	char* data;
	uint32_t orig_length;
	bool directory;
} KCAPEntry;

//Extracting

KCAPEntry* read_kcapentry(FILE* input);
void print_kcapentry(KCAPEntry* entry);
void free_kcapentry(KCAPEntry* entry);
int extract_kcap(FILE* input_file_handle, wchar_t* output_path);

//Packing

typedef struct KazusaEntry {
	wchar_t* name;
	bool folder;
	char* data;
	uint32_t size;
	struct KazusaEntry* inside;
	struct KazusaEntry* next;
	int is_root;
} KazusaEntry;

KazusaEntry* NewKazusaEntry();
void FreeKazusaEntry(KazusaEntry* entry);
extern int number_of_entries;
int PopulateKazusaEntry(KazusaEntry* entry, wchar_t *path);
KazusaEntry* InitKazusaPackageList(wchar_t *path);
void PrintKazusaPackageList(KazusaEntry* root, int level);
void KazusaPackageListFree(KazusaEntry* root);

void PackIt(KazusaEntry* root, FILE* handle, bool compressed);
uint32_t IndexIt(KazusaEntry* root, FILE* handle, int total_written,
                 int processed_entries, bool compressed);

void write_kcap_header(FILE* file);