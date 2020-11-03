#pragma once
#include <discord_rpc.h>
class RPCHandler {
public:
	void init();
	void setRPC(char* buf, char* buf2, const char* imgkey, const char* imgtext);
	bool enabled;
};
