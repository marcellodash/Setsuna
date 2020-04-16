#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <unistd.h>
#include <stdlib.h>
#include <config.h>

typedef struct KazusaApp {
	wchar_t* input;
	wchar_t* output;
	wchar_t* option;
	wchar_t* skip;
	FILE* input_file;
	wchar_t **wargv;
	int argc;
} KazusaApp;

KazusaApp* OpenKazusa(int argc, char* argv[]);
void CloseKazusa(KazusaApp* handle);

bool KazusaFileExist (wchar_t* name);
bool KazusaAppAskForPermissionDir();
bool KazusaDirectoryExist(wchar_t* name);
void KazusaExtract(KazusaApp* handle);
void KazusaPack(KazusaApp* handle);
void KazusaUnknown(KazusaApp* handle);