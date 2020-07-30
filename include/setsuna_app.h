/*******************************************************************************
*	<setsuna_app.h> - github.com/hiroshil/Setsuna
*	Author: @RaphaSanOri,@Hiroshil
*	Content: App Interface Declarations
*
*	This file is part of the Setsuna app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/hiroshil/Setsuna/blob/master/LICENSE.TXT
*/

#pragma once
#include <config.h>
#include <stdlib.h>

typedef struct SetsunaApp {
	char* input;
	char* output;
	char* option;
	char* skip;
	FILE* input_file;
} SetsunaApp;

SetsunaApp* OpenSetsuna(int argc, char* argv[]);
void CloseSetsuna(SetsunaApp* handle);
bool SetsunaAppAskForPermissionDir();
void SetsunaExtract(SetsunaApp* handle);
void SetsunaPack(SetsunaApp* handle);
void SetsunaUnknown(SetsunaApp* handle);
void SetsunaHelp();