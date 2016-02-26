#pragma once

#include <boost/asio.hpp>
#include <memory>

namespace Network
{
	using Socket = boost::asio::ip::tcp::socket;

	class IConnection
	{
		//отключить клиента
		virtual void DeleteConnection(const std::string &_clientGuid) = 0;
		
		//возвращает ссылку на io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//обработка сообщения
		virtual void HandleMessage(const std::string &_clientGuid, const std::string &_clientMsg) = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
		//возвращает ссылку на io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//передает серверу смарт-поинтер на сокет для создания подключения
		virtual void CreateConnection(std::shared_ptr<Socket> &pSocket) = 0;

		virtual ~IAcceptor() = default;
	};
}
