#include "SystemHandler.h"
#include "../RPCHandler/RPCHandler.h"
#include "../Main.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sysinfoapi.h>
#include <WinUser.h>
#include <pdh.h>
#include <ostream>
#include <tchar.h>

#pragma warning(disable : 4996)

using namespace std;

double getcurcpu();
long gbRAM;
LPSTR activestr;
LPSTR err;

static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;

int loop()
{
	cout << "Systemhandler Initialized\n";
	while (true) {
        vector<wstring> titles;
		char tit[256];
        HWND active = GetForegroundWindow();
        GetWindowText(active, tit, sizeof(tit));
        EnumWindows(winenum, reinterpret_cast<LPARAM>(&titles));
		
        char buffer[420];
        char buff2 [420];
        MEMORYSTATUSEX memInfo;
		
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG virtualMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
        virtualMemUsed = virtualMemUsed / (1024 * 1024 * 1024);
		
        DWORDLONG totram = memInfo.ullTotalPhys;
        totram = totram / (1024 * 1024 * 1024);
		
        sprintf(buffer, "%d Windows open | Active - %s", titles.size(), tit);
        sprintf(buff2, "%i/%igb RAM | %i%% CPU", (int)virtualMemUsed, (int)totram + 1, (int)getcurcpu());
        rpc->setRPC(buffer, buff2, "win", "Windows 10");
		
        Sleep(333);
	}
	return 0;
}


double getcurcpu() {
    PDH_FMT_COUNTERVALUE counterVal;
    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	
    return counterVal.doubleValue;
}

void SystemHandler::WINDOWS::init() {
    PdhOpenQuery(NULL, NULL, &cpuQuery);
    PdhAddEnglishCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
    PdhCollectQueryData(cpuQuery);
	
	HANDLE THREAD = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)loop, NULL, NULL, NULL);
	
	if (!THREAD)
		cout << "Failed to create thread.";
}

BOOL CALLBACK winenum(HWND hwnd, LPARAM lParam) {
    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];
    GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

    int length = ::GetWindowTextLength(hwnd);
    wstring title(&windowTitle[0]);
	
    if (!IsWindowVisible(hwnd) || !IsWindow(hwnd) || !IsWindowEnabled(hwnd) || !IsWindowUnicode(hwnd)|| length == 0 || title == L"Start" || title == L"Program Manager" || title == L"View Available Networks (Tooltip)")
        return TRUE;
		
    std::vector<std::wstring>& titles =
        *reinterpret_cast<std::vector<std::wstring>*>(lParam);
	
    titles.push_back(title);

    return TRUE;
}
