#pragma once

#include "ServerInterface.h"

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
			clientGuid(_guid)
		{}

		//начать прослушивание сокета
		void ReadMessage();

		//записать сообщение в сокет
		void WriteMessage(const std::string &message);

		//отменить все операции и перестать прослушивать сокет
		void Disconnect();

	private:
		//обработчик чтения
		void OnRead(const system::error_code &_error, const std::size_t _bytes);

		IConnection &rServer;//ссылка на интерфейс сервера
		SocketPtr pSocket;//указатель на сокет

		asio::streambuf writeBuffer;
		asio::streambuf readBuffer;

		const std::string clientGuid;//гуид пользователя(ник)
		const char delimiter{ '\0' };//символ до которого идет чтение данных в сокете
	};
}