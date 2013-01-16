#ifndef _Client_H
#define _Client_H

#include <SDL/SDL_net.h>

class Client{
private:
	IPaddress ip;
	TCPsocket socket;
	int* dataToSend;
	int* dataToRecv;

public:
	Client();
	~Client();

	void sendpackets();
};

#endif