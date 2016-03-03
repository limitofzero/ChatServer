#pragma once
#include "ICommand.h"
#include <boost/asio.hpp>

namespace Command
{
	//�������� �������� ������ ����������
	class CreateConnection : ICommand
	{
	public:
		


		//��������� ��������
		void Execute(Server &_server) override;

	private:
		const std::string clientGuid;
		SocketPtr pSocket;
	};
}
