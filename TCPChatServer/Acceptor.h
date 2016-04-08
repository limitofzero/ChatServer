#pragma once

#include "ServerInterface.h"
#include <boost/log/trivial.hpp>

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
			asioAcceptor(rService, endPoint),
			socket(rService)
		{
		}

		//������ �������� �����������
		void Start();
	
	private:
		//���������� �����������
		void OnAccept(const system::error_code &_error_code);

		IAcceptor &rServer;//������ �� ������
		asio::io_service &rService;//������ �� io_service
		const uint16_t tcpPort;//����, ������� ������� ������ ������
		asio::ip::tcp::endpoint endPoint;
		asio::ip::tcp::acceptor asioAcceptor;
		asio::ip::tcp::socket socket;
		
	};
}