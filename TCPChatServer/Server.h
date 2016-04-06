#pragma once
#include "ServerInterface.h"
#include "Connection.h"
#include "Acceptor.h"
#include "Settings.h"
#include "Parser.h"
#include <unordered_map>


namespace ChatServer
{
	using namespace boost;

	//класс, выполн€ющий ф-ии сервера
	class Server : 
		public IConnection, 
		public IAcceptor, 
		public ICommand
	{
		using ConnectionList = std::unordered_map<std::string, std::shared_ptr<Connection>>;

	public:
		Server();
		
		//возвращает ссылку на io_service
		asio::io_service &GetIOService() override
		{
			return io_service;
		}

		//интерфейс IConnection

		//отключить клиента и удалить его из списка подключений
		void DeleteConnection(const std::string &guid, const bool authorized = false) override;

		//обработка сообщени€
		void HandleMessage(const std::string &guid, const std::string &message) override;

		//авторизаци€
		void AuthorizeConnection(const std::string &tempGuid, const std::string &message) override;

		//возвращаем врем€ отключени€
		std::chrono::seconds GetDisconnectTime() const override
		{
			return disconnectTime;
		}

		//интерфейс IAcceptor

		//передает серверу смарт-поинтер на сокет дл€ создани€ подключени€
		void CreateConnection(SocketPtr &socket) override;

		//интерфейс дл€ выполнени€ команд сервера

		//отправить сообщение пользовател€м
		virtual void WriteMessage(const std::string &guid, const std::string &message) override;

		//добавить соединение в список проверенных
		virtual void AddAuthorizedConnection(const std::string &tempGuid, const std::string &newGuid) override;

	private:
		
		//унифицированный интерфейс удалени€ подключени€
		void DisconnectFromList(ConnectionList &list, const std::string &guid);

		asio::io_service io_service;//дл€ вызова ассинхронных ф-ий
		Acceptor acceptor;//слушает сокет на предмет подключений
		JsonParser::Parser jsParser;//служит дл€ парсинг сообщений(в/из json формат)

		const std::chrono::seconds disconnectTime;//врем€ отключени€ соединени€ от сервера(в секундах)
		uint32_t connectionsCounter;//счетчик подключений
		
		ConnectionList newConnections;//список неавторизированных подключений(ключ - временный гуид)
		ConnectionList authorizedConnections;//список авторизированных подключений(ключ - гуид(логин))
	};
}