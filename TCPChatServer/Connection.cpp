#include "Connection.h"
#include <boost\log\trivial.hpp>

void ChatServer::Connection::ReadMessage(const bool _first = false)
{
	auto pSelf(shared_from_this());
	asio::async_read_until(*pSocket, readBuffer, delimiter,
		[this, pSelf, _first](const system::error_code & _error, const std::size_t _bytes)
	{
		if (_error)
		{
			if (_error != system::errc::operation_canceled)
				BOOST_LOG_TRIVIAL(error) << _error.message();
			return;
		}

		OnRead(_error, _bytes, _first);
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

void ChatServer::Connection::StartDisconnectTimer()
{
	disconnectTimer.expires_from_now(disconnectTime);
	disconnectTimer.async_wait([this](const system::error_code &_error)
	{
		TimerHandler(_error);
	});
}

void ChatServer::Connection::ResetDisconnectTimer()
{
	disconnectTimer.cancel();//сбрасываем таймер
	StartDisconnectTimer();//запускаем таймер
}

void ChatServer::Connection::OnRead(const system::error_code & _error, const std::size_t _bytes, const bool _first)
{

	if (_bytes != 0)
	{
		//выводим данные из буфера в переменную
		std::istream in(&readBuffer);
		std::string receiveMsg;
		in >> receiveMsg;

		if (_first)//это первое сообщение?
		{
			rServer.AuthorizeConnection(clientGuid, receiveMsg);
			return;
		}
		else
		{
			//вызываем обработчик сервера
			rServer.HandleMessage(clientGuid, receiveMsg);
		}
	}

	ReadMessage();//продолжаем чтение
}

void ChatServer::Connection::TimerHandler(const system::error_code & _error)
{
	if (_error)
	{
		if (_error != system::errc::operation_canceled)
		{
			BOOST_LOG_TRIVIAL(error) << _error.message();
		}
	}

	//разорвать соединение
	rServer.DeleteConnection(clientGuid);
}
