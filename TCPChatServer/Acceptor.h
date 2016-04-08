#pragma once

#include "ServerInterface.h"
#include <boost/log/trivial.hpp>

namespace ChatServer
{
	using namespace boost;

	//класс, обеспечивающий прием новых подключений
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

		//начать ожидание подключения
		void Start();
	
	private:
		//обработчик подключения
		void OnAccept(const system::error_code &_error_code);

		IAcceptor &rServer;//ссылка на сервер
		asio::io_service &rService;//ссылка на io_service
		const uint16_t tcpPort;//порт, который слушает данный сервер
		asio::ip::tcp::endpoint endPoint;
		asio::ip::tcp::acceptor asioAcceptor;
		asio::ip::tcp::socket socket;
		
	};
}