#pragma once

#include "ShortEnums.h"

namespace Command
{
	using namespace ChatServer;

	class Server;
	//интерфейс для класса - комманда
	class BaseCommand
	{
		//выполнить комманду
		virtual void Execute(Server &_server) = 0;
	};
}