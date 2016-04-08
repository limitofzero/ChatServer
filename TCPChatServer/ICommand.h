#pragma once

#include "ServerInterface.h"



namespace Command
{
	//интерфейс для класса - комманда
	class ICommand
	{
	public:
		//выполнить комманду
		virtual void Execute(ChatServer::ICommandInterface &_server) = 0;
	};
}