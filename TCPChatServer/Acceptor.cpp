#include "Acceptor.h"
#include <boost/log/trivial.hpp>

void ChatServer::Acceptor::Start()
{
	//�������������� ����� �����
	SocketPtr pSocket = std::make_shared<Socket>(rService);

	//�������� ������� �����
	asioAcceptor.async_accept(*pSocket, endPoint, 
		[this, pSocket] (const system::error_code &_errorCode)
	{
		OnAccept(_errorCode, pSocket);
	});
}

void ChatServer::Acceptor::OnAccept(const system::error_code & _errorCode, SocketPtr _pSocket)
{
	if (_errorCode)
	{
		if (_errorCode != system::errc::operation_canceled)
			BOOST_LOG_TRIVIAL(error) << _errorCode.message();
	}
	else
	{
		//���� ������������ ��� ������
		rServer.CreateConnection(_pSocket);
	}

	Start();//����� �������� ���������
}
