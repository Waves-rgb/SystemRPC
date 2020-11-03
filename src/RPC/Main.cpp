#include "SystemHandler/SystemHandler.h"
#include "RPCHandler/RPCHandler.h"
#include "Main.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
bool windows = true;
#endif // win


RPCHandler* rpc;
SystemHandler::WINDOWS* syshandler;

using namespace std;

int main() {
	cout << "Initializing DiscordRPC\n";
#ifdef _WIN32
	SetConsoleTitle("System RPC for Discord");
#endif // win
	auto rpc = new RPCHandler();
	rpc->init();
	if (windows) {
		syshandler = new SystemHandler::WINDOWS;
		cout << "Initializing Systemhandler\n";
		syshandler->init();
	}

	while (true)
	{
		Sleep(1000);
	}
}