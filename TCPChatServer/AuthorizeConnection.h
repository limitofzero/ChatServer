#pragma once
#include "ICommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//комманда создания нового соединения
	class AuthorizeConnection : public ICommand
	{
	public:
		AuthorizeConnection(const std::string &_temp_guid, const std::string &_new_guid,
			const std::string &_client_password) :
			tempGuid(_temp_guid),
			clientGuid(_new_guid),
			clientPassword(_client_password)
		{};


		//выполнить комманду
		void Execute(ChatServer::ICommand &_server) override
		{
			_server.AddAuthorizedConnection(tempGuid, clientGuid);
		}

	private:
		const std::string clientGuid;
		const std::string tempGuid;
		const std::string clientPassword;
	};
}
