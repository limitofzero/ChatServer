#include "Server.h"


int main()
{
	setlocale(0, "");
	ChatServer::Server server;
	server.Start();
	
	std::cin.get();
	return 0;
}