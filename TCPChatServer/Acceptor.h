#pragma once

#include "ServerInterface.h"

namespace ChatServer
{
	using namespace boost;

	//класс, обеспечивающий прием новых подключений
	class Acceptor
	{
	public:
		Acceptor(IAcceptor &_rServer, uint16_t _tcpPort) :
			rServer(_rServer),
			rService(_rServer.GetIOService()),
			tcpPort(_tcpPort),
			endPoint(asio::ip::tcp::v4(), tcpPort),
			asioAcceptor(_rServer.GetIOService(), asio::ip::tcp::v4())
		{}

	
	
	private:
		IAcceptor &rServer;//ссылка на сервер
		asio::io_service &rService;//ссылка на io_service
		asio::ip::tcp::acceptor asioAcceptor;
		const uint16_t tcpPort;//порт, который слушает данный сервер
		const asio::ip::tcp::endpoint endPoint;//точка подключения
	};
}