#ifndef _Client_H
#define _Client_H

#include <SDL/SDL_net.h>
#include <string>

class Client{
private:
	IPaddress ip;
	TCPsocket socket;

	bool connected;

public:
	Client(std::string host, Uint16 port);
	~Client();
	void sendData(void *data, Uint32 size);
	bool receiveData(void *data, Uint32 size);
};

#endif