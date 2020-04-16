#include <config.h>
#include <kazusa_app.h>
#include <lzss.h>
#include <util.h>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");

	KazusaApp* app = OpenKazusa(argc, argv);

	switch (app->option[0]) {
	case L'e':
		KazusaExtract(app);
		break;
	case L'p':
		KazusaPack(app);
		break;
	default:
		KazusaUnknown(app);
		break;
	}
	CloseKazusa(app);
}

