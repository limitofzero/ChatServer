#pragma once
#include "ICommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//�������� �������� ������ ����������
	class CreateConnection : ICommand
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
