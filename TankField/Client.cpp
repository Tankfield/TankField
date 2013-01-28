#include "Client.h"

Client::Client(std::string host, Uint16 port)
:connected(true) {	
	SDLNet_ResolveHost(&ip, host.c_str(), port);		
	socket = SDLNet_TCP_Open(&ip);	
}

Client::~Client(){
	SDLNet_TCP_Close(socket);
}

bool Client::receiveData(void *data, Uint32 size) {
	if (connected) {		
		if ((SDLNet_TCP_Recv(socket, data, size)) > 0) {
			return true;
		}	
	}

	return false;
}

void Client::sendData(void *data, Uint32 size) {
	if (connected) {
		SDLNet_TCP_Send(socket, data, size);
	}
}