#include <gvl/support/platform.hpp>
#include <exception>
#include <string>
#ifdef SWITCH
#include <switch.h>
#ifdef NXLINK
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <unistd.h>
#endif
#endif

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
#ifdef WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif // WIN32

#ifdef main
#undef main
#endif

int main(int argc, char *argv[])
{
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
	#ifdef SWITCH
	#ifdef NXLINK
	socketInitializeDefault();
	nxlinkStdio();
	printf("Remote stdout active...\n");
	#endif
	Result rc = romfsInit();
	if (R_FAILED(rc))
	{
		printf("romfsInit failed: %08X\n", rc);
		return 1;
	}
	#endif

	return gameEntry(argc, argv);
	
	#ifdef SWITCH
	romfsExit();
	#endif
}
#endif
