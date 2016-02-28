#pragma once

#include <boost/asio.hpp>
#include <memory>

namespace ChatServer
{
	using Socket = boost::asio::ip::tcp::socket;
	using SocketPtr = std::shared_ptr<Socket>;

	class IConnection
	{
	public:
		//отключить клиента
		virtual void DeleteConnection(const std::string &_clientGuid) = 0;
		
		//возвращает ссылку на io_service --------- возможно убрать!!!!!!!!!!!!!!!!
		virtual boost::asio::io_service &GetIOService() = 0;

		//обработка сообщения
		virtual void HandleMessage(const std::string &_clientGuid, const std::string &_clientMsg) = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
	public:
		//возвращает ссылку на io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//передает серверу смарт-поинтер на сокет для создания подключения
		virtual void CreateConnection(SocketPtr &_pSocket) = 0;

		virtual ~IAcceptor() = default;
	};


	class IAuthorizator
	{
	public:
		//добавляет прошедшего авторизацию пользователя на сервер
		virtual void AddConnection(const std::string &_guid, SocketPtr &_socket) = 0;

		//возвращает ссылку на io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		virtual ~IAuthorizator() = default;
	};
}
