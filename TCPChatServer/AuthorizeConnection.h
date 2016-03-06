#pragma once
#include "ICommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//комманда создания нового соединения
	class AuthorizeConnection : ICommand
	{
	public:
		AuthorizeConnection(const std::string &_temp_guid, const std::string &_new_guid,
			const std::string &_client_version) :
			tempGuid(_temp_guid),
			clientGuid(_new_guid),
			clientVersion(_client_version)
		{};


		//выполнить комманду
		void Execute(ChatServer::ICommand &_server) override
		{
			_server.AddAuthorizedConnection(tempGuid, clientGuid);
		}

	private:
		const std::string clientGuid;
		const std::string tempGuid;
		const std::string clientVersion;
	};
}
