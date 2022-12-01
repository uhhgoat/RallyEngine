
#include "Rally.h"

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Rally::Run();

	Rally::Delete();

	return 0;
}

