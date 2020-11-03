#include "RPCHandler.h"
#include <discord_rpc.h>
#include <iostream>
void handleDiscordReady(const DiscordUser* request);
bool enabled = true;
void handleDiscordError(int errorCode, const char* message);

void RPCHandler::init()
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.errored = handleDiscordError;
    Discord_Initialize("589137984603947053", &handlers, 1, "");
    std::cout << "RPC Init complete.\n";
}
void handleDiscordReady(const DiscordUser* request) {
    std::cout << "Connected to user: " << request->username << "\n";
}
void handleDiscordError(int errorCode, const char* message) {
    std::cout << "RPC ERROR "<< errorCode << "!\n\t" << message;
}
void RPCHandler::setRPC(char* buf, char* buf2, const char* imgkey, const char* imgtext) {
    DiscordRichPresence* rpc = new DiscordRichPresence();

    rpc->details = buf;
    rpc->state = buf2;
    rpc->largeImageKey = imgkey;
    rpc->largeImageText = imgtext;
   
    Discord_UpdatePresence(rpc);
}