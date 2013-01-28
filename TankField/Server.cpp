#include "Server.h"

Server::Server(Uint16 port) 
: running(false), connected(false) {	
	SDLNet_ResolveHost(&ip, NULL, port);		
	listenSocket = SDLNet_TCP_Open(&ip);
}

Server::~Server() {
	SDLNet_TCP_Close(listenSocket);
	SDLNet_TCP_Close(clientSocket);
}

void Server::start() {
	running = true;
}

void Server::stop() {
	running = false;
}

bool Server::isRunning() {
	return running;
}

bool Server::clientConnected() {
	if (connected) {
		return true;
	}
	else if(clientSocket = SDLNet_TCP_Accept(listenSocket)){
		connected = true;
	}

	return false;
}

bool Server::receiveData(void *data, Uint32 size) {
	if (connected) {		
		if ((SDLNet_TCP_Recv(clientSocket, data, size)) > 0) {
			return true;
		}	
	}

	return false;
}

void Server::sendData(void *data, Uint32 size) {
	if (connected) {
		SDLNet_TCP_Send(clientSocket, data, size);
	}
}