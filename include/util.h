/*******************************************************************************
*	<util.h> - github.com/raphasanori/Kazusa
*	Author: @RaphaSanOri
*	Content: Util Function Declarations
*
*	This file is part of the Kazusa app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/raphasanori/Kazusa/blob/master/LICENSE.TXT
*/

#pragma once

#include <config.h>

void normalize_string(char* string);
void denormalize_string(char* string);
char* sjis2utf8(char* sjis);
char* utf82sjis(char* utf8, int* size);