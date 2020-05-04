/*******************************************************************************
*	<kazusa_app.h> - github.com/raphasanori/Kazusa
*	Author: @RaphaSanOri
*	Content: App Interface Declarations
*
*	This file is part of the Kazusa app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/raphasanori/Kazusa/blob/master/LICENSE.TXT
*/

#pragma once
#include <config.h>
#include <stdlib.h>

typedef struct KazusaApp {
	char* input;
	char* output;
	char* option;
	char* skip;
	FILE* input_file;
} KazusaApp;

KazusaApp* OpenKazusa(int argc, char* argv[]);
void CloseKazusa(KazusaApp* handle);
bool KazusaAppAskForPermissionDir();
void KazusaExtract(KazusaApp* handle);
void KazusaPack(KazusaApp* handle);
void KazusaUnknown(KazusaApp* handle);
void KazusaHelp();