/*******************************************************************************
*	<main.c> - github.com/hiroshil/Setsuna
*	Author: @RaphaSanOri,@Hiroshil
*	Content: Main Program Definition
*
*	This file is part of the Setsuna app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/hiroshil/Setsuna/blob/master/LICENSE.TXT
*/

#include <setsuna_app.h>
#include <locale.h>

int main(int argc, char* argv[]) {
	init_victorique();

	SetsunaApp* app = OpenSetsuna(argc, argv);

	switch (app->option[0]) {
	case 'e':
		SetsunaExtract(app);
		break;
	case 'p':
		SetsunaPack(app);
		break;
	default:
		SetsunaUnknown(app);
		break;
	}
	CloseSetsuna(app);

	destroy_victorique();
}

