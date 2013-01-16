#ifndef _Server_H
#define _Server_H
#include <SDL/SDL_net.h>

class Server{
private:
	IPaddress ip;
	TCPsocket socket;
	TCPsocket socket2;

	int* dataToSend;
	int* dataToRecv;
public:

	Server();
	~Server();
	void createConnection();
	void recievePackets();

};



#endif