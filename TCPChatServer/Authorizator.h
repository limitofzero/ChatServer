#pragma once

#include "ServerInterface.h"
#include <unordered_map>
#include <chrono>
#include <boost/asio/basic_deadline_timer.hpp>

namespace ChatServer
{
	using namespace boost;

	class BaseParser;
	//класс, авторизирующий подключения
	class Authorizator
	{
		using BufferPtr = std::shared_ptr<asio::streambuf>;

	public:
		Authorizator(IAuthorizator &_server, const uint16_t _disconnect_seconds) :
			rServer(_server),
			rService(_server.GetIOService()),
			disconnectSeconds(_disconnect_seconds)
			//код инициализации парсера
		{}

		//добавить подключение
		void WaitAuthorizedMessage(SocketPtr &_socket);

	private:
		//обработчик чтения
		void OnRead(const system::error_code &_error ,SocketPtr _socket, BufferPtr _buffer);

		//обработчик отключения
		void TimeOut(SocketPtr _socket);

		IAuthorizator &rServer;//ссылка на сервер
		asio::io_service &rService;//ссылка на io_services
		std::unique_ptr<BaseParser> pParser;//парсер
		const std::chrono::seconds disconnectSeconds;//время отключения(для таймера)
	};
}