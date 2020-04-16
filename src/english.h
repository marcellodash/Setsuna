#pragma once

#ifdef ENGLISH_LANGUAGE
#define NEW_LINE L"\n"
#define TAB L"\t"
#define SOFTWARE_NAME L"Kazusa"
#define SOFTWARE_VERSION L"v1.0"
#define SOFTWARE_HEADER L"" NEW_LINE TAB TAB SOFTWARE_NAME " " SOFTWARE_VERSION NEW_LINE NEW_LINE
#define SEPARATOR_LINE L"==================================================" NEW_LINE

#define ARROW L"=> "
#define WARNING_PARAMETERS L"[WARNING] This program needs 3 parameters!" NEW_LINE
#define CHECK_INSTRUCTIONS L"Check the instructions below!" NEW_LINE
#define WARNING_BOX L"" NEW_LINE SEPARATOR_LINE ARROW WARNING_PARAMETERS ARROW CHECK_INSTRUCTIONS SEPARATOR_LINE NEW_LINE

#define UNKNOWN_OPTION L"Unknown option" NEW_LINE
#define UNKNOWN_BOX L"" NEW_LINE SEPARATOR_LINE ARROW UNKNOWN_OPTION ARROW CHECK_INSTRUCTIONS SEPARATOR_LINE NEW_LINE

#define UNKNOWN_SKIP L"Unknown skip option" NEW_LINE
#define UNKNOWN_SKIPBOX L"" NEW_LINE SEPARATOR_LINE ARROW UNKNOWN_SKIP ARROW CHECK_INSTRUCTIONS SEPARATOR_LINE NEW_LINE

#define USAGE L"Usage:" NEW_LINE
#define USAGE_CMD_LINE L"" TAB SOFTWARE_NAME ".exe [option] input output [skip]" NEW_LINE NEW_LINE
#define OPTIONS L"Options:" NEW_LINE
#define OPTION_E L"" TAB "e = extract" NEW_LINE
#define OPTION_P L"" TAB "p = pack" NEW_LINE
#define SKIP_SWITCH L"Skip (optional):" NEW_LINE
#define SKIP_YES L"" TAB "y = Will skip all questions with always [yes]" NEW_LINE
#define SKIP_NO L"" TAB "n = Will skip all questions with always [no]" NEW_LINE
#define AUTH_FILE_CREATION L"Authorize " SOFTWARE_NAME " to create file?" NEW_LINE
#define AUTH_DIR_CREATION L"Authorize " SOFTWARE_NAME " to create directory?" NEW_LINE
#define QUESTION_YES_NO L"Please choise between (y) for yes and (n) for no" NEW_LINE
#define YOUR_CHOICE L"Your choice?: "
#define NOT_UNDERSTAND_CHOICE L"Couldn't recognize your choise..." NEW_LINE

#define NO_MOD_STORAGE_DONE L"No modifications to your storage were done!" NEW_LINE
#define RUN_AGAIN_FILE L"Please run again with a valid file!" NEW_LINE
#define RUN_AGAIN_DIR L"Please run again with a valid directory!" NEW_LINE
#define OR_AUTH_CREATION L"Or authorize the creation of one!" NEW_LINE

#define USER_AUTH_FILE L"User authorized the file creation!" NEW_LINE
#define USER_PREAUTH_FILE L"User pre-authorized the file creation!" NEW_LINE
#define USER_AUTH_DIR L"User authorized the directory creation!" NEW_LINE
#define USER_PREAUTH_DIR L"User pre-authorized the directory creation!" NEW_LINE

#define OUTPUT_DIR_EXISTS L"Output directory exists!" NEW_LINE
#define OUTPUT_DIR_NOTEXISTS L"Output directory doesn't exists!" NEW_LINE

#define USER_OPTED_DIR L"User opted to create the directory!" NEW_LINE
#define USER_PREOPTED_DIR L"User pre-opted to create the directory!" NEW_LINE

#define USER_OPTEDNOT_DIR L"User opted to not create the directory!" NEW_LINE
#define USER_PREOPTEDNOT_DIR L"User pre-opted to not create the directory!" NEW_LINE

#define DIR_CREATED_SUCCESS L"The directory was created successfully!" NEW_LINE
#define FILE_CREATED_SUCCESS L"The file was created successfully!" NEW_LINE

#define APP_FINISHING L"Finishing..." NEW_LINE

#define INIT_EXTRACTION L"Initializing extraction..." NEW_LINE
#define INPUT_FILE L"Input file = "
#define OUTPUT_DIR L"Output directory = "
#define INPUT_SUCCESS L"Input opened successfully!" NEW_LINE
#define INPUT_FAIL L"Couldn't open input, check your parameters" NEW_LINE

#define INIT_PACKAGING L"Initializing packing..." NEW_LINE
#define INPUT_DIR L"Input directory = "
#define OUTPUT_FILE L"Output file = "

#define HELP_TEXT L"" SOFTWARE_HEADER USAGE USAGE_CMD_LINE OPTIONS OPTION_E OPTION_P SKIP_SWITCH SKIP_YES SKIP_NO

#define INPUT_WRONG_TYPE L"File can't be handled, exiting..." NEW_LINE
#define INPUT_TYPE_CONFIRM L"File can be handled!" NEW_LINE
#define INPUT_TYPE_LABEL L"INPUT TYPE: "

#define FILE_HAVE_N_ENTRIES L"Number of entries found: "
#define KCAPENTRY_LOG_FORMAT L"%ls (%d) (c=%d)" NEW_LINE
#define FILE_NO_DATA L"Weird compressed length (no data?)" NEW_LINE

#define ALL_ENTRIES_PROCESSED L"All entries processed" NEW_LINE
#define SOME_ENTRIES_NOT_PROCESSED L"Some entries may not have been processed" NEW_LINE

#define KCAPENTRYBEGIN L"KCAPEntry {" NEW_LINE
#define FILENAME TAB L"FILENAME = "
#define COMPRESSED TAB L"COMPRESSED = "
#define UNKNOWN L"UNKNOWN"
#define OFFSET TAB L"OFFSET = "
#define LENGTH TAB L"LENGTH = "
#define ORIGINALLENGTH TAB L"ORIGINAL LENGTH = "
#define ISDIRECTORY TAB L"IS DIRECTORY" NEW_LINE
#define ISFILE TAB L"IS FILE" NEW_LINE
#define KCAPENTRYEND L"}" NEW_LINE

#define DATAONBEGIN L"DATA ON (%ls) { "
#define DATAONEND L"\b\b}" NEW_LINE

#define DIR_LABEL L"dir"
#define FILE_LABEL L"file"
#define KAZUSAENTRILOGGER L"%ls is %ls" NEW_LINE
#define INPUT_DIR_EXISTS L"Input directory exist" NEW_LINE
#define LISTING_INPUT_ENTRIES L"Listing and loading entries..." NEW_LINE
#define NUM_OF_ENTRIES_FOUND L"Number of entries found = "
#define INDEXING_ENTRIES L"Indexing entries..." NEW_LINE
#define PACKING_ENTRIES L"Packing entries..." NEW_LINE
#define PACKING_DONE L"Packing done!" NEW_LINE
#define INPUT_DIR_PROBLEM L"Input directory doesn't exist or have blocking permissions" NEW_LINE


#endif