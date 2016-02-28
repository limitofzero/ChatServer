#pragma once

#include "ServerInterface.h"
#include <boost/asio/system_timer.hpp>

namespace ChatServer
{

	using namespace boost;
	//класс, обеспечивающий работу с подключением(отпарвка/прием сообщений/отключение)
	class Connection : std::enable_shared_from_this<Connection>
	{
	public:
		Connection(IConnection &_server, SocketPtr &_socket, const std::string _guid) :
			rServer(_server),
			pSocket(std::move(_socket)),
			disconnectTime(_server.GetDisconnectTime()),
			disconnectTimer(_server.GetIOService()),
			clientGuid(_guid)
		{}

		//начать прослушивание сокета
		void ReadMessage(const bool _first = false);

		//записать сообщение в сокет
		void WriteMessage(const std::string &message);

		//отменить все операции и перестать прослушивать сокет
		void Disconnect();

		//запуск таймера отключения
		void StartDisconnectTimer();

		//сброс таймера отключения
		void ResetDisconnectTimer();

	private:
		//обработчик чтения
		void OnRead(const system::error_code &_error, const std::size_t _bytes, const bool _first);

		//обработчик событий таймера
		void TimerHandler(const system::error_code &_error);

		IConnection &rServer;//ссылка на интерфейс сервера
		SocketPtr pSocket;//указатель на сокет

		asio::streambuf writeBuffer;
		asio::streambuf readBuffer;

		asio::system_timer disconnectTimer;//таймер отключения
		const std::chrono::seconds disconnectTime;//время, спустя которе должен срабатывать таймер

		const std::string clientGuid;//гуид пользователя(ник)
		const char delimiter{ '\0' };//символ до которого идет чтение данных в сокете
	};
}