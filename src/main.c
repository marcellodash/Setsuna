/*******************************************************************************
*	<main.c> - github.com/raphasanori/Kazusa
*	Author: @RaphaSanOri
*	Content: Main Program Definition
*
*	This file is part of the Kazusa app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/raphasanori/Kazusa/blob/master/LICENSE.TXT
*/

#include <kazusa_app.h>
#include <locale.h>

int main(int argc, char* argv[]) {
	init_victorique();

	KazusaApp* app = OpenKazusa(argc, argv);

	switch (app->option[0]) {
	case 'e':
		KazusaExtract(app);
		break;
	case 'p':
		KazusaPack(app);
		break;
	default:
		KazusaUnknown(app);
		break;
	}
	CloseKazusa(app);

	destroy_victorique();
}

