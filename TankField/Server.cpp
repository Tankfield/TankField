#include "Server.h"

Server::Server(){
	SDLNet_Init();
	SDLNet_ResolveHost(&ip, NULL, 2000);
	socket = SDLNet_TCP_Open(&ip);	
}

Server::~Server(){
	SDLNet_TCP_Close(socket);
	SDLNet_TCP_Close(socket2);
}

void Server::createConnection(){
	socket2 = SDLNet_TCP_Accept(socket);
}

void Server::recievePackets(){
	SDLNet_TCP_Recv(socket2, dataToRecv, 1024);
}