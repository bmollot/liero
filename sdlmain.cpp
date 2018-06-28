#include <gvl/support/platform.hpp>
#include <exception>
#include <string>

#ifdef DEBUG_FILE
// Needed for logging
#include <unistd.h>
#include <fcntl.h>
#endif

int gameEntry(int argc, char *argv[]);

#if GVL_WINDOWS && !defined(DISABLE_MAINHACK)
// A bit of a hack to avoid DLL dependencies
#define _WIN32_WINDOWS 0x0410
#define WINVER 0x0410
#include <windows.h>
#include <SDL/SDL.h>

#ifdef main
#undef main
#endif

int main(int argc, char *argv[])
{
	SDL_SetModuleHandle(GetModuleHandle(NULL));

	try
	{	
		return gameEntry(argc, argv);
	}
	catch(std::exception& ex)
	{
		MessageBoxA(NULL, (std::string("Sorry, something went wrong :(\r\n\r\n") + ex.what()).c_str(), "Liero", MB_OK | MB_ICONWARNING);
		return 1;
	}
}
#else
int main(int argc, char *argv[])
{
	#if defined(DEBUG_FILE)
	// Clone stdout to a file, as default stdout on Switch
	// isn't accessible.
	int log = open(DEBUG_FILE, O_WRONLY);
	dup2(log, 1);
	printf("Started...\n");
	#endif
	return gameEntry(argc, argv);
}
#endif
