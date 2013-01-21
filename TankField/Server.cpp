#include "Server.h"

Server::Server(){
	SDLNet_ResolveHost(&ip, NULL, 9999);
	socket = SDLNet_TCP_Open(&ip);
	/*if(!socket){
		exit(1);
	}*/
}

Server::~Server(){
	SDLNet_TCP_Close(socket);
	SDLNet_TCP_Close(socket2);
}

void Server::createConnection(){
	if(!socket){
		socket = SDLNet_TCP_Open(&ip);
	}
	if(socket != NULL){
		if((socket2 = SDLNet_TCP_Accept(socket))){
			recievePackets();
		}
	}
}

void Server::recievePackets(){
	SDLNet_TCP_Recv(socket2, recievedData, 1024);
}

int Server::getWeaponDegrees(){
	return recievedData[0];
}

int Server::getTankPositionX(){
	return recievedData[1];
}

bool Server::isConnected(){
	if(!socket2){
		return true;
	}
	return false;
}
