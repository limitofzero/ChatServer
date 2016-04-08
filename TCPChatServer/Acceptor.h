#pragma once

#include "ServerInterface.h"

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
			asioAcceptor(rService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), tcpPort))
		{}

		//начать ожидание подключения
		void Start();
	
	private:
		//обработчик подключения
		void OnAccept(const system::error_code &_error_code, SocketPtr _socket);

		IAcceptor &rServer;//ссылка на сервер
		asio::io_service &rService;//ссылка на io_service
		asio::ip::tcp::acceptor asioAcceptor;
		const uint16_t tcpPort;//порт, который слушает данный сервер
	};
}