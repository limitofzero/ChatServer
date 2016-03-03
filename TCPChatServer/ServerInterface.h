#pragma once


#include "ShortEnums.h"
#include <chrono>

namespace ChatServer
{
	class ParametrizedMessage;

	class IConnection
	{
	public:
		//отключить клиента
		virtual void DeleteConnection(const std::string &_guid) = 0;
		
		//возвращает ссылку на io_service --------- возможно убрать!!!!!!!!!!!!!!!!
		virtual boost::asio::io_service &GetIOService() = 0;

		//обработка сообщения
		virtual void HandleMessage(const std::string &_guid, const std::string &_message) = 0;

		//авторизация
		virtual void AuthorizeConnection(const std::string &_temp_guid, const std::string &_message) = 0;

		//возвращаем время отключения
		virtual std::chrono::seconds GetDisconnectTime() = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
	public:
		//возвращает ссылку на io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//передает серверу смарт-поинтер на сокет для создания подключения
		virtual void CreateConnection(SocketPtr &_socket) = 0;

		virtual ~IAcceptor() = default;
	};

	//интерфейс для выполнения команд сервера
	class ICommand
	{
		//отправить сообщение пользователю/пользователям(в зависимости от _message)
		virtual void WriteMessage(const ParametrizedMessage _message) = 0;

		//добавить соединение в список проверенных
		virtual void AddAuthorizedConnection(const std::string &_temp_guid, const std::string &_new_guid) = 0;

		virtual ~ICommand() = default;
	};
}
