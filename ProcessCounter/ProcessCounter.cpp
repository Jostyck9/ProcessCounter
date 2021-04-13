#include <iostream>
#include <windows.h>
#include <sysinfoapi.h>
#include <psapi.h>

/**
* Print the number of process with the current time of the system
*
* @param cProcesses number of processes currently running of the computer
*
**/
void printProcessCount(DWORD cProcesses) {
	SYSTEMTIME time;

	GetLocalTime(&time);
	printf("%04d.%02d.%02d %02d:%02d:%02d : %lu\n", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, cProcesses);
}

/**
* Fetch the number of processes currently running on the computer
*
* @param cProcesses pointer to the variable to fill with the number of processes currently running
* @return true if got all the processes, false if an error occured
*
**/
bool getProcessCount(DWORD* cProcesses) {
	DWORD aProcesses[1024], cbNeeded;

	if (cProcesses == nullptr || !EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		return false;
	}
	*cProcesses = cbNeeded / sizeof(DWORD);
	return true;
}

int main()
{
	DWORD cProcesses;

	while (1) {
		if (getProcessCount(&cProcesses)) {
			printProcessCount(cProcesses);
			Sleep(1000);
		}
		else {
			std::cerr << "Couldn't retrieve the processes" << std::endl;
			return -1;
		}
	}
	return 0;
}