#pragma once
#include "BaseCommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//комманда создания нового соединения
	class CreateConnection : BaseCommand
	{
	public:
		CreateConnection(const std::string _guid, SocketPtr &_socket) :


		//выполнить комманду
		void Execute(Server &_server) override;

	private:
		const std::string clientGuid;
		SocketPtr pSocket;
	};
}
