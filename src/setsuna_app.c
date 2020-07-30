/*******************************************************************************
*	<setsuna_app.c> - github.com/hiroshil/Setsuna
*	Author: @RaphaSanOri,@Hiroshil
*	Content: App Interface Definitions
*
*	This file is part of the Setsuna app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/hiroshil/Setsuna/blob/master/LICENSE.TXT
*/

#include <setsuna_app.h>
#include <kcap.h>
#include <string.h>
#include <sys/stat.h>
#include <locale.h>
#include <util.h>
//#include <windows.h>


SetsunaApp* OpenSetsuna(int argc, char* argv[]) {
	SetsunaApp* handle = (SetsunaApp*)malloc(sizeof(SetsunaApp));
	handle->option = NULL;
	handle->input = NULL;
	handle->output = NULL;
	handle->skip = NULL;
	handle->input_file = NULL;
	//SetConsoleOutputCP(65001);
	setlocale(LC_ALL, "en_US.utf8");

	if (argc <= 1) {
		SetsunaHelp();
		CloseSetsuna(handle);
	} else if (argc <= 3) {
		printf("[WARNING] This program needs 3 parameters!\nCheck the instructions below!\n");
		SetsunaHelp();
		CloseSetsuna(handle);
	} else if (argc <= 4) {
		handle->option = argv[1];
		handle->input = argv[2];
		handle->output = argv[3];
	} else {
		handle->option = argv[1];
		handle->input = argv[2];
		handle->output = argv[3];
		handle->skip = argv[4];
	}
	return handle;
}

void SetsunaHelp() {
	printf("\n\t\tSetsuna %s\n", SOFTWARE_VERSION);
	printf("Usage:\n\
        \t\tSetsuna.exe [option] input output [skip]\n\
\n\
Options:\n\
        \t\te = extract\n\
        \t\tp = pack\n\
Skip (optional):\n\
        \t\ty = Will skip all questions with always [yes]\n\
        \t\tn = Will skip all questions with always [no]");
}

bool SetsunaAppAskForPermissionDir() {
	printf("Authorize Setsuna to create directory?\n");
	printf("Please choise between (y) for yes and (n) for no\n");
	printf("Your choice?:");
	char str [80];
	scanf ("%s", str);
	while ((str[0] != 'y') && (str[0] != 'n')) {
		printf("\nCouldn't recognize your choise...\n");
		printf("Please choise between (y) for yes and (n) for no\n");
		printf("Your choice?:");
		scanf ("%s", str);
	}
	if (str[0] == 'y') {
		return true;
	} else {
		return false;
	}
}

void CloseSetsuna(SetsunaApp* handle) {
	if (handle != NULL) {
		if (handle->input_file != NULL) {
			fclose(handle->input_file);
		}
		free(handle);
	}
	printf("Finishing...\n");
	exit(EXIT_SUCCESS);
}

void SetsunaExtract(SetsunaApp* handle) {
	printf("\n\t\tSetsuna %s\n", SOFTWARE_VERSION);
	printf("Init extract\n");
	printf("Input: %s\n", handle->input);
	printf("Output: %s\n\n", handle->output);

	if (file_exist(handle->input)) {
		printf("Input success!\n");
		handle->input_file = fopen(handle->input, "rb");
		char magic_string[5] = {0, 0, 0, 0, 0};
		fseek(handle->input_file, 0, SEEK_SET);
		fread(magic_string, 4, 1, handle->input_file);
		if (strcmp(magic_string, "KCAP") == 0) {
			printf("This file can be handled\n");
		} else {
			printf("Can't handle this file\n");
			CloseSetsuna(handle);
		}
	} else {
		printf("Couldn't open input\n");
		CloseSetsuna(handle);
	}
	printf("\n");

	if (dir_exist(handle->output)) {
		printf("Output directory exist!\n");
	} else {
		printf("Output directory doesn't exist!\n");
		if (handle->skip) {
			switch (handle->skip[0]) {
			case 'y':
				printf("User already authorized dir creation\n");
				mkdir(handle->output);
				printf("Dir created successfully!\n");
				break;
			case 'n':
				printf("User didn't authorized dir creation, nothing was modified\n");
				CloseSetsuna(handle);
				break;
			default:
				printf("Error with arguments\n");
				SetsunaHelp();
				CloseSetsuna(handle);
				break;
			}
		} else {
			if (SetsunaAppAskForPermissionDir()) {
				printf("User already authorized dir creation\n");
				mkdir(handle->output);
				printf("Dir created successfully!\n");
			} else {
				printf("\nUser didn't authorized dir creation, nothing was modified\n");
				CloseSetsuna(handle);
			}
		}
	}

	if (extract_kcap(handle->input_file, handle->output) < 0) {
		CloseSetsuna(handle);
	}

}

void SetsunaPack(SetsunaApp* handle) {
	printf("\n\t\tSetsuna %s\n", SOFTWARE_VERSION);
	printf("Init extract\n");
	printf("Input: %s\n", handle->input);
	printf("Output: %s\n\n", handle->output);

	if (dir_exist(handle->input)) {
		printf("Input exist!\n");
		printf("Listing and loading entries...\n");

		SetsunaEntry* root = InitSetsunaPackageList(handle->input);
		printf("Entries found = %d\n", number_of_entries);

		FILE *file_to_write;
		//file_to_write = fopen(handle->output, "wb");
		file_to_write = _wfopen(GetWC(string_to_hex(handle->output), strlen(handle->output)), L"wb");
		write_kcap_header(file_to_write);

		printf("Indexing...\n");
		IndexIt(root, file_to_write, 0, 0, false);
		printf("Packing...\n");
		PackIt(root, file_to_write, false);

		fclose(file_to_write);
		SetsunaPackageListFree(root);
		printf("Packing done!\n");
	} else {
		printf("Couldn't find input directory\n");
		CloseSetsuna(handle);
	}
}

void SetsunaUnknown(SetsunaApp* handle) {
	printf("Unknown option\n");
	SetsunaHelp();
}