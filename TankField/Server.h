#ifndef _Server_H
#define _Server_H
#include <SDL/SDL_net.h>

class Server{
private:
	IPaddress ip;
	TCPsocket socket;
	TCPsocket socket2;

	int dataToSend[1024];
	int recievedData[1024];
public:
	
	Server();
	~Server();
	void createConnection();
	void recievePackets();
	int getWeaponDegrees();
	int getTankPositionX();
	bool isConnected();
};



#endif