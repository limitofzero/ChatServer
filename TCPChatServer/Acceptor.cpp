#include "Acceptor.h"
#include <boost/log/trivial.hpp>

namespace ChatServer
{

	void Acceptor::Start()
	{
		//�������������� ����� �����
		SocketPtr pSocket = std::make_shared<Socket>(rService);

		//�������� ������� �����
		asioAcceptor.async_accept(*pSocket,
			[this, pSocket](const system::error_code &_errorCode)
		{
			OnAccept(_errorCode, pSocket);
		});
	}

	void Acceptor::OnAccept(const system::error_code & _errorCode, SocketPtr pSocket)
	{
		if (_errorCode)
		{
			if (_errorCode != asio::error::operation_aborted)
			{
				BOOST_LOG_TRIVIAL(error) << _errorCode.message();
				return;
			}
		}
		else
		{
			//���� ������������ ��� ������
			rServer.CreateConnection(pSocket);
		}

		Start();//����� �������� ���������
	}
}