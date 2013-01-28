#ifndef _Server_H
#define _Server_H
#include <SDL/SDL_net.h>

class Server{
	private:
		bool running;
		bool connected;

		IPaddress ip;
		TCPsocket listenSocket;
		TCPsocket clientSocket;

	public:
		Server(Uint16 port);
		~Server();

		// not usable for now
		void start();
		void stop();
		bool isRunning();
		//////////////////////
		bool clientConnected();
		bool receiveData(void *data, Uint32 size);
		void sendData(void *data, Uint32 size);
};



#endif