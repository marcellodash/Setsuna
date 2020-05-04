/*******************************************************************************
*	<kazusa_app.c> - github.com/raphasanori/Kazusa
*	Author: @RaphaSanOri
*	Content: App Interface Definitions
*
*	This file is part of the Kazusa app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/raphasanori/Kazusa/blob/master/LICENSE.TXT
*/

#include <kazusa_app.h>
#include <kcap.h>
#include <string.h>
#include <sys/stat.h>

KazusaApp* OpenKazusa(int argc, char* argv[]) {
	KazusaApp* handle = (KazusaApp*)malloc(sizeof(KazusaApp));
	handle->option = NULL;
	handle->input = NULL;
	handle->output = NULL;
	handle->skip = NULL;
	handle->input_file = NULL;

	if (argc <= 1) {
		KazusaHelp();
		CloseKazusa(handle);
	} else if (argc <= 3) {
		printf("[WARNING] This program needs 3 parameters!\nCheck the instructions below!\n");
		KazusaHelp();
		CloseKazusa(handle);
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

void KazusaHelp() {
	printf("\n\t\tKazusa %s\n", SOFTWARE_VERSION);
	printf("Usage:\n\
        \t\tKazusa.exe [option] input output [skip]\n\
\n\
Options:\n\
        \t\te = extract\n\
        \t\tp = pack\n\
Skip (optional):\n\
        \t\ty = Will skip all questions with always [yes]\n\
        \t\tn = Will skip all questions with always [no]");
}

bool KazusaAppAskForPermissionDir() {
	printf("Authorize Kazusa to create directory?\n");
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

void CloseKazusa(KazusaApp* handle) {
	if (handle != NULL) {
		if (handle->input_file != NULL) {
			fclose(handle->input_file);
		}
		free(handle);
	}
	printf("Finishing...\n");
	exit(EXIT_SUCCESS);
}

void KazusaExtract(KazusaApp* handle) {
	printf("\n\t\tKazusa %s\n", SOFTWARE_VERSION);
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
			CloseKazusa(handle);
		}
	} else {
		printf("Couldn't open input\n");
		CloseKazusa(handle);
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
				CloseKazusa(handle);
				break;
			default:
				printf("Error with arguments\n");
				KazusaHelp();
				CloseKazusa(handle);
				break;
			}
		} else {
			if (KazusaAppAskForPermissionDir()) {
				printf("User already authorized dir creation\n");
				mkdir(handle->output);
				printf("Dir created successfully!\n");
			} else {
				printf("\nUser didn't authorized dir creation, nothing was modified\n");
				CloseKazusa(handle);
			}
		}
	}

	if (extract_kcap(handle->input_file, handle->output) < 0) {
		CloseKazusa(handle);
	}

}

void KazusaPack(KazusaApp* handle) {
	printf("\n\t\tKazusa %s\n", SOFTWARE_VERSION);
	printf("Init extract\n");
	printf("Input: %s\n", handle->input);
	printf("Output: %s\n\n", handle->output);

	if (dir_exist(handle->input)) {
		printf("Input exist!\n");
		printf("Listing and loading entries...\n");

		KazusaEntry* root = InitKazusaPackageList(handle->input);
		printf("Entries found = %d\n", number_of_entries);

		FILE *file_to_write;
		file_to_write = fopen(handle->output, "wb");
		write_kcap_header(file_to_write);

		printf("Indexing...\n");
		IndexIt(root, file_to_write, 0, 0, false);
		printf("Packing...\n");
		PackIt(root, file_to_write, false);

		fclose(file_to_write);
		KazusaPackageListFree(root);
		printf("Packing done!\n");
	} else {
		printf("Couldn't find input directory\n");
		CloseKazusa(handle);
	}
}

void KazusaUnknown(KazusaApp* handle) {
	printf("Unknown option\n");
	KazusaHelp();
}