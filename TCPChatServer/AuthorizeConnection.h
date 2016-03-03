#pragma once
#include "ICommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//�������� �������� ������ ����������
	class AuthorizeConnection : ICommand
	{
	public:
		AuthorizeConnection(const std::string &_temp_guid, const std::string &_new_guid) :
			tempGuid(_temp_guid),
			clientGuid(_new_guid)
		{};


		//��������� ��������
		void Execute(ChatServer::ICommand &_server) override;

	private:
		const std::string clientGuid;
		const std::string tempGuid;
	};
}
