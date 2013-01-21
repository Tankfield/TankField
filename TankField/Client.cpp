#include "Client.h"

Client::Client(){
	SDLNet_ResolveHost(&ip,"localhost", 2000);
	socket = SDLNet_TCP_Open(&ip);
}

Client::~Client(){
	SDLNet_TCP_Close(socket);
}

void Client::sendPackets(){
	if(socket){
		SDLNet_TCP_Send(socket, dataToSend, 1024);
	}
}

void Client::setWeaponDegrees(int degrees){
	dataToSend[0] = degrees;
}