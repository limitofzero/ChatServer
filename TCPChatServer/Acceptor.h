#pragma once

#include "ServerInterface.h"

namespace ChatServer
{
	using namespace boost;

	//�����, �������������� ����� ����� �����������
	class Acceptor
	{
	public:
		Acceptor(IAcceptor &_rServer, uint16_t _tcpPort) :
			rServer(_rServer),
			rService(_rServer.GetIOService()),
			tcpPort(_tcpPort),
			endPoint(asio::ip::tcp::v4(), tcpPort),
			asioAcceptor(rService, asio::ip::tcp::v4())
		{}

		//������ �������� �����������
		void Start();
	
	private:
		//���������� �����������
		void OnAccept(const system::error_code &_errorCode, SocketPtr _pSocket);

		IAcceptor &rServer;//������ �� ������
		asio::io_service &rService;//������ �� io_service
		asio::ip::tcp::acceptor asioAcceptor;
		const uint16_t tcpPort;//����, ������� ������� ������ ������
		const asio::ip::tcp::endpoint endPoint;//����� �����������
	};
}