#include "Connection.h"
#include <boost\log\trivial.hpp>

void ChatServer::Connection::ReadMessage()
{
	auto pSelf(shared_from_this());
	asio::async_read_until(*pSocket, readBuffer, delimiter,
		[this, pSelf](const system::error_code & _error, const std::size_t _bytes)
	{
		OnRead(_error, _bytes);
	});
}

void ChatServer::Connection::WriteMessage(const std::string & message)
{
	auto pSelf(shared_from_this());

	//пишем сообщение в буфер
	std::ostream out(&writeBuffer);
	out << message;

	//пишем в сокет
	asio::async_write(*pSocket, writeBuffer,
		[this, pSelf](const system::error_code & _error, const std::size_t _bytes)
	{
		if (_error)
		{
			if (_error != system::errc::operation_canceled)
				BOOST_LOG_TRIVIAL(error) << _error.message();
		}
	});
}

void ChatServer::Connection::Disconnect()
{
	pSocket->shutdown(Socket::shutdown_both);
	pSocket->close();
}

void ChatServer::Connection::OnRead(const system::error_code & _error, const std::size_t _bytes)
{
	if (_error)
	{
		if (_error != system::errc::operation_canceled)
			BOOST_LOG_TRIVIAL(error) << _error.message();
		return;
	}

	if (_bytes != 0)
	{
		//выводим данные из буфера в переменную
		std::istream in(&readBuffer);
		std::string receiveMsg;
		in >> receiveMsg;

		//вызываем обработчик сервера
		rServer.HandleMessage(clientGuid, receiveMsg);
	}

	ReadMessage();//продолжаем чтение
}
