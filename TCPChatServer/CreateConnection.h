#pragma once
#include "BaseCommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//�������� �������� ������ ����������
	class CreateConnection : BaseCommand
	{
	public:
		CreateConnection(const std::string _guid, SocketPtr &_socket) :


		//��������� ��������
		void Execute(Server &_server) override;

	private:
		const std::string clientGuid;
		SocketPtr pSocket;
	};
}
