#include <kazusa_app.h>
#include <kcap.h>

KazusaApp* OpenKazusa(int argc, char* argv[]) {
	KazusaApp* handle = (KazusaApp*)malloc(sizeof(KazusaApp));
	handle->option = NULL;
	handle->input = NULL;
	handle->output = NULL;
	handle->skip = NULL;
	handle->input_file = NULL;
	handle->argc = argc;
	handle->wargv = (wchar_t **)malloc(handle->argc * sizeof(wchar_t *));

	for (int i = 0; i < handle->argc; i++) {
		int size = (strlen(argv[i]) * sizeof(wchar_t)) + 1;
		handle->wargv[i] = (wchar_t *)malloc(size);
		mbstowcs(handle->wargv[i], argv[i], size);
	}

	setlocale(LC_ALL, "");
	if (handle->argc <= 1) {
		PRINTL(HELP_TEXT);
		CloseKazusa(handle);
	} else if (handle->argc <= 3) {
		PRINTL(WARNING_BOX);
		PRINTL(HELP_TEXT);
	} else if (handle->argc <= 4) {
		handle->option = handle->wargv[1];
		handle->input = handle->wargv[2];
		handle->output = handle->wargv[3];
	} else {
		handle->option = handle->wargv[1];
		handle->input = handle->wargv[2];
		handle->output = handle->wargv[3];
		handle->skip = handle->wargv[4];
	}
	return handle;
}

bool KazusaAppAskForPermissionDir() {
	PRINTL(AUTH_DIR_CREATION QUESTION_YES_NO YOUR_CHOICE);
	wchar_t str [80];
	wscanf (L"%ls", str);
	while ((str[0] != L'y') && (str[0] != L'n')) {
		PRINTL(NEW_LINE);
		PRINTL(NOT_UNDERSTAND_CHOICE QUESTION_YES_NO YOUR_CHOICE);
		wscanf (L"%ls", str);
	}
	if (str[0] == L'y') {
		return true;
	} else {
		return false;
	}
}

void CloseKazusa(KazusaApp* handle) {
	if (handle != NULL) {
		if (handle->wargv != NULL) {
			for (int i = 0; i < handle->argc; i++) {
				if (handle->wargv[i] != NULL) {
					free(handle->wargv[i]);
				}
			}
			free(handle->wargv);
		}

		if (handle->input_file != NULL) {
			fclose(handle->input_file);
		}
		free(handle);
	}
	PRINTL(APP_FINISHING);
	exit(EXIT_SUCCESS);
}

bool KazusaFileExist (wchar_t* name) {
	return  _waccess( name, F_OK ) != -1 ;
}

bool KazusaDirectoryExist(wchar_t* name) {
	struct _stat32 info;

	if (_wstat( name, &info ) != 0)
		return false;
	else if (info.st_mode & S_IFDIR)
		return true;
	else
		return false;
}

void KazusaExtract(KazusaApp* handle) {
	PRINTL(SOFTWARE_HEADER);
	PRINTL(INIT_EXTRACTION);
	PRINTL_S(INPUT_FILE, handle->input);
	PRINTL_S(OUTPUT_DIR, handle->output);
	PRINTL(NEW_LINE);

	if (KazusaFileExist(handle->input)) {
		PRINTL(INPUT_SUCCESS);
		handle->input_file = _wfopen(handle->input, L"rb");
		char magic_string[5] = {0, 0, 0, 0, 0};
		fseek(handle->input_file, 0, SEEK_SET);
		fread(magic_string, 4, 1, handle->input_file);
		PRINTL_ASCII(INPUT_TYPE_LABEL, magic_string);
		if (strcmp(magic_string, "KCAP") == 0) {
			PRINTL(INPUT_TYPE_CONFIRM);
		} else {
			PRINTL(INPUT_WRONG_TYPE);
			CloseKazusa(handle);
		}
	} else {
		PRINTL(INPUT_FAIL);
		CloseKazusa(handle);
	}
	PRINTL(NEW_LINE);

	if (KazusaDirectoryExist(handle->output)) {
		PRINTL(OUTPUT_DIR_EXISTS);
	} else {
		PRINTL(OUTPUT_DIR_NOTEXISTS);
		if (handle->skip) {
			switch (handle->skip[0]) {
			case L'y':
				PRINTL(USER_PREAUTH_DIR);
				_wmkdir(handle->output);
				PRINTL(DIR_CREATED_SUCCESS);
				break;
			case L'n':
				PRINTL(USER_PREOPTEDNOT_DIR);
				PRINTL(NO_MOD_STORAGE_DONE RUN_AGAIN_DIR OR_AUTH_CREATION);
				CloseKazusa(handle);
				break;
			default:
				PRINTL(UNKNOWN_SKIPBOX);
				PRINTL(HELP_TEXT);
				CloseKazusa(handle);
				break;
			}
		} else {
			if (KazusaAppAskForPermissionDir()) {
				PRINTL(USER_AUTH_DIR);
				_wmkdir(handle->output);
				PRINTL(DIR_CREATED_SUCCESS);
			} else {
				PRINTL(NEW_LINE);
				PRINTL(USER_OPTEDNOT_DIR);
				PRINTL(NO_MOD_STORAGE_DONE RUN_AGAIN_DIR OR_AUTH_CREATION);
				CloseKazusa(handle);
			}
		}
	}

	if (extract_kcap(handle->input_file, handle->output) < 0) {
		CloseKazusa(handle);
	}

}

void KazusaPack(KazusaApp* handle) {
	PRINTL(SOFTWARE_HEADER);
	PRINTL(INIT_PACKAGING);
	PRINTL_S(INPUT_DIR, handle->input);
	PRINTL_S(OUTPUT_FILE, handle->output);
	PRINTL(NEW_LINE);

	if (KazusaDirectoryExist(handle->input)) {
		PRINTL(INPUT_DIR_EXISTS);
		PRINTL(LISTING_INPUT_ENTRIES);

		KazusaEntry* root = InitKazusaPackageList(handle->input);
		PRINTL_UINT32(NUM_OF_ENTRIES_FOUND, number_of_entries);

		FILE *file_to_write;
		file_to_write = _wfopen(handle->output, L"wb");
		write_kcap_header(file_to_write);

		PRINTL(INDEXING_ENTRIES);
		IndexIt(root, file_to_write, 0, 0, false);
		PRINTL(PACKING_ENTRIES);
		PackIt(root, file_to_write, false);

		fclose(file_to_write);
		KazusaPackageListFree(root);
		PRINTL(PACKING_DONE);
	} else {
		PRINTL(INPUT_DIR_PROBLEM);
		CloseKazusa(handle);
	}
}

void KazusaUnknown(KazusaApp* handle) {
	PRINTL(UNKNOWN_BOX);
	PRINTL(HELP_TEXT);
}