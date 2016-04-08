#pragma once


#include "ShortEnums.h"
#include <chrono>

namespace ChatServer
{
	class IConnection
	{
	public:
		//отключить клиента
		virtual void DeleteConnection(const std::string &guid, const bool authorized = false) = 0;
		
		//возвращает ссылку на io_service --------- возможно убрать!!!!!!!!!!!!!!!!
		virtual boost::asio::io_service &GetIOService() = 0;

		//обработка сообщения
		virtual void HandleMessage(const std::string &guid, const std::string &message) = 0;

		//авторизация
		virtual void AuthorizeConnection(const std::string &tempGuid, const std::string &message) = 0;

		//возвращаем время отключения
		virtual std::chrono::seconds GetDisconnectTime() const = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
	public:
		//возвращает ссылку на io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//передает серверу смарт-поинтер на сокет для создания подключения
		virtual void CreateConnection(SocketPtr &socket) = 0;

		virtual ~IAcceptor() = default;
	};

	//интерфейс для выполнения команд сервера
	class ICommandInterface
	{
	public:
		//отправить сообщение пользователям
		virtual void WriteClientMessage(const std::string &message) = 0;

		//добавить соединение в список проверенных
		virtual void AddAuthorizedConnection(const std::string &tempGuid, const std::string &newGuid) = 0;

		virtual ~ICommandInterface() = default;
	};
}
