/*******************************************************************************
*	<kcap.h> - github.com/hiroshil/Setsuna
*	Author: @RaphaSanOri,@Hiroshil
*	Content: KCAP Archive Function Declarations
*
*	This file is part of the Setsuna app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/hiroshil/Setsuna/blob/master/LICENSE.TXT
*/

#pragma once
#include <config.h>

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
int extract_kcap(FILE* input_file_handle, char* output_path);

//Packing

typedef struct SetsunaEntry {
	wchar_t* name;
	bool folder;
	char* data;
	uint32_t size;
	struct SetsunaEntry* inside;
	struct SetsunaEntry* next;
	int is_root;
} SetsunaEntry;

SetsunaEntry* NewSetsunaEntry();
void FreeSetsunaEntry(SetsunaEntry* entry);
extern int number_of_entries;
int PopulateSetsunaEntry(SetsunaEntry* entry, char *path);
SetsunaEntry* InitSetsunaPackageList(char *path);
void PrintSetsunaPackageList(SetsunaEntry* root, int level);
void SetsunaPackageListFree(SetsunaEntry* root);

void PackIt(SetsunaEntry* root, FILE* handle, bool compressed);
uint32_t IndexIt(SetsunaEntry* root, FILE* handle, int total_written,
                 int processed_entries, bool compressed);

void write_kcap_header(FILE* file);