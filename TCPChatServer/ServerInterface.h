#pragma once


#include "ShortEnums.h"

namespace ChatServer
{
	class IConnection
	{
	public:
		//отключить клиента
		virtual void DeleteConnection(const std::string &_guid) = 0;
		
		//возвращает ссылку на io_service --------- возможно убрать!!!!!!!!!!!!!!!!
		virtual boost::asio::io_service &GetIOService() = 0;

		//обработка сообщения
		virtual void HandleMessage(const std::string &_guid, const std::string &_message) = 0;

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
}
