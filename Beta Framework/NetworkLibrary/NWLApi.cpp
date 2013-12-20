#include "NWLApi.h"

using namespace std;

/*
 * Initializes Socket API for use depending on what platform the code is running on.
 */
int InitializeNWL() {
	int iResult = 0;
#ifdef _WIN32
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		std::cout << "Error: Initializing NWL (WinSocks) failed -- " << iResult << std::endl;
		return 1;
	}
#endif
	return 0;
}
