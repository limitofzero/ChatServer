#pragma once
#include "ICommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//комманда создания нового соединения
	class CreateConnection : ICommand
	{
	public:
		


		//выполнить комманду
		void Execute(Server &_server) override;

	private:
		const std::string clientGuid;
		SocketPtr pSocket;
	};
}
