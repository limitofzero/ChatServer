#pragma once

#include "ServerInterface.h"
#include "ShortEnums.h"

namespace Command
{
	using namespace ChatServer;

	class Server;
	//интерфейс для класса - комманда
	class ICommand
	{
	public:
		//выполнить комманду
		virtual void Execute(ChatServer::ICommand &_server) = 0;
	};
}