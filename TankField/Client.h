#ifndef _Client_H
#define _Client_H

#include <SDL/SDL_net.h>

class Client{
private:
	IPaddress ip;
	TCPsocket socket;
	int dataToSend[1024];
	int dataToRecv[1024];

public:
	Client();
	~Client();

	void sendPackets();
	void setWeaponDegrees(int degrees);
};

#endif