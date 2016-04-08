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

	//класс, выполняющий ф-ии сервера
	class Server : 
		public IConnection, 
		public IAcceptor, 
		public ICommandInterface
	{
		using ConnectionList = std::unordered_map<std::string, std::shared_ptr<Connection>>;

	public:

		Server() :
			acceptor(*this, Settings::Instance().port),
			disconnectTime(Settings::Instance().secondsToDisconnect)
		{}

		void Start()
		{
			acceptor.Start();
		}
		
		//возвращает ссылку на io_service
		asio::io_service &GetIOService() override
		{
			return io_service;
		}

		//отправляет сообщение контректному пользователю
		void WriteMessage(const std::string &guid, const std::string &message);

		//интерфейс IConnection

		//отключить клиента и удалить его из списка подключений
		void DeleteConnection(const std::string &guid, const bool authorized = false) override;

		//обработка сообщения
		void HandleMessage(const std::string &guid, const std::string &message) override;

		//авторизация
		void AuthorizeConnection(const std::string &tempGuid, const std::string &message) override;

		//возвращаем время отключения
		std::chrono::seconds GetDisconnectTime() const override
		{
			return disconnectTime;
		}

		//интерфейс IAcceptor

		//передает серверу смарт-поинтер на сокет для создания подключения
		void CreateConnection(SocketPtr &socket) override;

		//интерфейс для выполнения команд сервера

		//разослать сообщение пользователям
		virtual void WriteClientMessage(const std::string &message) override;

		//добавить соединение в список проверенных
		virtual void AddAuthorizedConnection(const std::string &tempGuid, const std::string &newGuid) override;

	private:
		
		//унифицированный интерфейс удаления подключения
		void DisconnectFromList(ConnectionList &list, const std::string &guid);

		asio::io_service io_service;//для вызова ассинхронных ф-ий
		Acceptor acceptor;//слушает сокет на предмет подключений
		JsonParser::Parser jsParser;//служит для парсинг сообщений(в/из json формат)

		const std::chrono::seconds disconnectTime;//время отключения соединения от сервера(в секундах)
		uint32_t connectionsCounter;//счетчик подключений
		
		ConnectionList newConnections;//список неавторизированных подключений(ключ - временный гуид)
		ConnectionList authorizedConnections;//список авторизированных подключений(ключ - гуид(логин))
	};
}