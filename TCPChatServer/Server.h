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
		void DeleteConnection(const std::string &_guid) override;

		//обработка сообщени€
		void HandleMessage(const std::string &_guid, const std::string &_message) override;

		//авторизаци€
		void AuthorizeConnection(const std::string &_temp_guid, const std::string &_message) override;

		//возвращаем врем€ отключени€
		std::chrono::seconds GetDisconnectTime() override;



	private:
		asio::io_service io_service;//дл€ вызова ассинхронных ф-ий
		Acceptor acceptor;//слушает сокет на предмет подключений
		JsonParser::Parser jsParser;//служит дл€ парсинг сообщений(в/из json формат)

		const std::chrono::seconds disconnectTime;//врем€ отключени€ соединени€ от сервера(в секундах)
		
		ConnectionList newConnections;//список неавторизированных подключений(ключ - временный гуид)
		ConnectionList authorizedConnections;//список авторизированных подключений(ключ - гуид(логин))
	};
}