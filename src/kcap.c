#include <kcap.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <lzss.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

//Extracting

KCAPEntry* read_kcapentry(FILE* input) {
	KCAPEntry* new_entry = malloc(sizeof(KCAPEntry));
	fread(&new_entry->compressed, 4, 1, input);
	new_entry->filename = malloc(25);
	memset(new_entry->filename, 0, 25);

	fread(new_entry->filename, 24, 1, input);
	fread(&new_entry->unknown, 8, 1, input);
	fread(&new_entry->offset, 4, 1, input);
	fread(&new_entry->length, 4, 1, input);

	if (new_entry->compressed == DIRECTORY_SIGN) {
		new_entry->directory = true;
	} else {
		new_entry->directory = false;
	}

	return new_entry;
}

void print_kcapentry(KCAPEntry* entry) {
	PRINTL(KCAPENTRYBEGIN);

	PRINTL_ASCII(FILENAME, entry->filename);
	PRINTL_UINT32(COMPRESSED, entry->compressed);
	PRINTL(TAB);
	PRINT_DATA(UNKNOWN, 8, &entry->unknown);
	PRINTL_UINT32(OFFSET, entry->offset);
	PRINTL_UINT32(LENGTH, entry->length);
	PRINTL_UINT32(ORIGINALLENGTH, entry->orig_length);
	if (entry->directory) {
		PRINTL(ISDIRECTORY);
	} else {
		PRINTL(ISFILE);
	}

	PRINTL(KCAPENTRYEND);

}

void free_kcapentry(KCAPEntry* entry) {
	if (entry != NULL) {
		if (entry->filename != NULL) {
			free(entry->filename);
		}
		free(entry);
	}
}

int extract_kcap(FILE* input_file_handle, wchar_t* output_path) {

	//Begin extraction
	fseek(input_file_handle, 12, SEEK_SET);
	uint32_t num_of_entries = read_uint32_t(input_file_handle);
	PRINTL_UINT32(FILE_HAVE_N_ENTRIES, num_of_entries);
	PRINTL(NEW_LINE);

	wchar_t* cur_dir = copy_string(output_path);
	bool last_was_dir = false;
	long save_file_pos = ftell(input_file_handle);
	int entries_got = 0;

	for (int i = 0; i < num_of_entries; i++) {
		//Restore file pos
		fseek(input_file_handle, save_file_pos, SEEK_SET);
		//Read new entry
		KCAPEntry* a = read_kcapentry(input_file_handle);
		//Convert filename
		wchar_t* fnamew = convert_string((char*)a->filename);

		if (a->directory) {
			if (last_was_dir) {
				wchar_t* old_cur = cur_dir;
				cur_dir = join_path(cur_dir, fnamew);
				free(old_cur);
			} else {
				wchar_t* old_cur = cur_dir;
				cur_dir = join_path(output_path, fnamew);
				if (old_cur != NULL) {
					free(old_cur);
				}
			}
			_wmkdir(cur_dir);
			PRINT_LOG_INDEX(KCAPENTRY_LOG_FORMAT, cur_dir, i + 1, -1);

			//Save file pos to continue extraction
			save_file_pos = ftell(input_file_handle);
		} else {
			//Save file pos to go to data
			save_file_pos = ftell(input_file_handle);

			int compressed_length;
			int original_length;
			char* original_data_buffer;
			char* compressed_data_buffer;

			fseek(input_file_handle, a->offset, SEEK_SET);
			if (a->compressed == 1) {
				compressed_length = read_uint32_t(input_file_handle);
				original_length = read_uint32_t(input_file_handle);
			} else {
				compressed_length = a->length;
				original_length = a->length;
			}

			if (a->compressed == 1) {
				//Fix seemly wrong compressed lengths
				//Header seems to always be right
				if (compressed_length != a->length)
					compressed_length = a->length;
			}

			//Remove the data header from the size
			if (a->compressed == 1)
				compressed_length -= 8;

			//If it become negative (weird case)
			//Just make the data header the data
			//And modify the original length
			if (a->compressed == 1) {
				if (compressed_length < 0) {
					compressed_length += 8;
					original_length = compressed_length;
					//And alter the position inside the file
					fseek(input_file_handle, save_file_pos, SEEK_SET);
					PRINTL(FILE_NO_DATA);
				}
			}

			compressed_data_buffer = malloc(compressed_length);
			original_data_buffer = malloc(original_length);

			if (original_data_buffer == NULL || compressed_data_buffer == NULL)
				return -1;

			fread(compressed_data_buffer, compressed_length, 1, input_file_handle);
			memset(original_data_buffer, 0, original_length);

			char* output_buffer;
			long output_size;

			if (a->compressed == 1) {
				if (decompress_lzss((uint8_t *)original_data_buffer,
				                    (uint8_t *)compressed_data_buffer, original_length) < 0) {
					return -1;
				}

				output_buffer = original_data_buffer;
				output_size = original_length;
			} else {
				output_buffer = compressed_data_buffer;
				output_size = compressed_length;
			}

			FILE *file_to_write;

			wchar_t* full_path = join_path(cur_dir, fnamew);
			normalize_string(full_path);
			PRINT_LOG_INDEX(KCAPENTRY_LOG_FORMAT, full_path, i + 1, a->compressed);

			file_to_write = _wfopen(full_path, L"wb");
			fwrite(output_buffer, output_size, 1, file_to_write);
			fclose(file_to_write);

			free(full_path);
			free(original_data_buffer);
			free(compressed_data_buffer);
		}
		last_was_dir = a->directory;

		free(fnamew);
		free_kcapentry(a);
		entries_got = i + 1;
	}
	if (entries_got == num_of_entries) {
		PRINTL(ALL_ENTRIES_PROCESSED);
	} else {
		PRINTL(SOME_ENTRIES_NOT_PROCESSED);
	}

	return 0;
}

//Packing
int number_of_entries;

KazusaEntry* NewKazusaEntry() {
	KazusaEntry* entry = malloc(sizeof(KazusaEntry));
	entry->name = NULL;
	entry->folder = false;
	entry->inside = NULL;
	entry->next = NULL;
	entry->data = NULL;
	entry->size = 0;
	entry->is_root = 0;
	number_of_entries++;
	return entry;
}

void FreeKazusaEntry(KazusaEntry* entry) {
	if (entry != NULL) {
		if (entry->name != NULL) {
			free(entry->name);
		}
		if (entry->folder == false) {
			if (entry->data != NULL) {
				free(entry->data);
			}
		}
		free(entry);
		number_of_entries--;
	}
}


int PopulateKazusaEntry(KazusaEntry* entry, wchar_t *path) {
	_WDIR *dir;
	struct _wdirent *ent;
	if (isDirectoryEmpty(path)) {
		return 0;
	}
	KazusaEntry* head = NewKazusaEntry();
	KazusaEntry* current = head;
	entry->inside = head;
	KazusaEntry* last = head;

	if ((dir = _wopendir (entry->name)) != NULL) {
		while ((ent = _wreaddir (dir)) != NULL) {
			if (wcscmp(ent->d_name, L".") && wcscmp(ent->d_name, L"..")) {
				wchar_t* full_path = join_path(path, ent->d_name);
				current->name = copy_string(full_path);
				current->folder = is_dir(full_path);

				if (current->folder) {
					PopulateKazusaEntry(current, full_path);
				} else {
					LoadToArray(full_path, &current->data, &current->size);
				}

				free(full_path);

				KazusaEntry* new_entry = NewKazusaEntry();
				current->next = new_entry;
				last = current;
				current = new_entry;
			}
		}
		if (current->name == NULL) {
			FreeKazusaEntry(current);
			last->next = NULL;
		}
		_wclosedir (dir);
		return 0;
	} else {
		return -1;
	}
}

KazusaEntry* InitKazusaPackageList(wchar_t *path) {
	KazusaEntry* root = NewKazusaEntry();
	root->folder = true;
	root->name = copy_string(path);
	PopulateKazusaEntry(root, path);
	number_of_entries--;
	root->is_root = 1;

	return root;
}

void PrintKazusaPackageList(KazusaEntry* root, int level) {
	KazusaEntry* current;
	current = root;
	while (current != NULL) {
		for (int i = 0; i < level; i++) {
			wprintf (TAB);
		}
		wprintf (KAZUSAENTRILOGGER, current->name, current->folder ? DIR_LABEL : FILE_LABEL);
		if (current->folder) {
			PrintKazusaPackageList(current->inside, level + 1);
		}
		current = current->next;
	}
}

void PackIt(KazusaEntry* root, FILE* handle, bool compressed) {
	KazusaEntry* current;
	current = root;
	while (current != NULL) {
		if (!current->folder) {
			if (current->is_root != 1) {
				if (compressed) {
					fwrite(&current->size, 4, 1, handle);
					fwrite(&current->size, 4, 1, handle);
				}
				fwrite(current->data, current->size, 1, handle);
			}
		} else {
			PackIt(current->inside, handle, compressed);
		}
		current = current->next;
	}
}

uint32_t IndexIt(KazusaEntry* root, FILE* handle, int total_written, int processed_entries, bool compressed) {
	KazusaEntry* current;
	current = root;
	uint32_t compressed_marker = 0;
	uint32_t folder_marker = 3435973836;
	uint8_t nothing_marker = 0;
	uint64_t misterious_marker = 281474976710655uL;

	while (current != NULL) {
		if (current->is_root != 1) {
			if (current->folder) {
				fwrite(&folder_marker, 4, 1, handle);
			} else {
				fwrite(&compressed_marker, 4, 1, handle);
			}
			denormalize_string(current->name);
			wchar_t* temp = _wstrrchr(current->name, '\\');
			temp++;

			char* temp2 = w2c(temp);
			int size = strlen(temp2) + 1;
			fwrite(temp2, size, 1, handle);

			for (int i = 0; i < 24 - size; i++) {
				fwrite(&nothing_marker, 1, 1, handle);
			}
			fwrite(&misterious_marker, 8, 1, handle);

			uint32_t offset = 4 + 8 + 4 + (44 * number_of_entries) + total_written;
			fwrite(&offset, 4, 1, handle);
			fwrite(&current->size, 4, 1, handle);

			if (!current->folder) {
				if (compressed)
					total_written += (current->size + 8);
				else
					total_written += (current->size /*+ 8*/);
			}
			processed_entries++;
			free(temp2);
		}
		if (current->folder) {
			total_written = IndexIt(current->inside, handle, total_written, processed_entries, compressed);
		}
		current = current->next;
	}
	return total_written;
}

void KazusaPackageListFree(KazusaEntry* root) {
	KazusaEntry* current;
	current = root;
	while (current != NULL) {
		if (current->folder) {
			KazusaPackageListFree(current->inside);
		}
		KazusaEntry* s = current;
		current = current->next;
		FreeKazusaEntry(s);
	}
}

void write_kcap_header(FILE* file) {
	char MAGIC[4] = "KCAP";
	uint64_t random = 281474976710655uL;
	fwrite(&MAGIC, 4, 1, file);
	fwrite(&random, 8, 1, file);
	fwrite(&number_of_entries, 4, 1, file);
}