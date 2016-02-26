#pragma once

#include "ServerInterface.h"

namespace ChatServer
{
	using namespace boost;

	//�����, �������������� ����� ����� �����������
	class Acceptor
	{
	public:
		Acceptor(IAcceptor &_server, uint16_t _port) :
			rServer(_server),
			rService(_server.GetIOService()),
			tcpPort(_port),
			endPoint(asio::ip::tcp::v4(), tcpPort),
			asioAcceptor(rService, asio::ip::tcp::v4())
		{}

		//������ �������� �����������
		void Start();
	
	private:
		//���������� �����������
		void OnAccept(const system::error_code &_error_code, SocketPtr _socket);

		IAcceptor &rServer;//������ �� ������
		asio::io_service &rService;//������ �� io_service
		asio::ip::tcp::acceptor asioAcceptor;
		const uint16_t tcpPort;//����, ������� ������� ������ ������
		const asio::ip::tcp::endpoint endPoint;//����� �����������
	};
}