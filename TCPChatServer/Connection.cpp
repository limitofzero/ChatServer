#include "Connection.h"
#include <boost\log\trivial.hpp>

namespace ChatServer
{

	void Connection::ReadMessage(const bool _first)
	{
		auto pSelf(shared_from_this());
		asio::async_read_until(socket, readBuffer, delimiter,
			[this, pSelf, _first](const system::error_code & _error, const std::size_t _bytes)
		{
			if (_error)
			{
				if (_error != asio::error::operation_aborted)
					BOOST_LOG_TRIVIAL(error) << _error.message();
				return;
			}

			OnRead(_error, _bytes, _first);
		});
	}

	void Connection::WriteMessage(const std::string &message)
	{
		auto pSelf(shared_from_this());

		//����� ��������� � �����
		std::ostream out(&writeBuffer);
		out << message;

		//����� � �����
		asio::async_write(socket, writeBuffer,
			[this, pSelf](const system::error_code & _error, const std::size_t _bytes)
		{
			if (_error)
			{
				if (_error != asio::error::operation_aborted)
					BOOST_LOG_TRIVIAL(error) << _error.message();
			}
		});
	}

	void Connection::Disconnect()
	{
		socket.shutdown(Socket::shutdown_both);
		socket.close();
	}

	void Connection::StartDisconnectTimer()
	{
		disconnectTimer.expires_from_now(disconnectTime);
		disconnectTimer.async_wait([this](const system::error_code &_error)
		{
			TimerHandler(_error);
		});
	}

	void Connection::ResetDisconnectTimer()
	{
		disconnectTimer.cancel();//���������� ������
		StartDisconnectTimer();//��������� ������
	}

	void Connection::OnRead(const system::error_code & _error, const std::size_t _bytes, const bool _first)
	{

		if (_bytes != 0)
		{
			//������� ������ �� ������ � ����������
			std::istream in(&readBuffer);
			std::string receiveMsg;
			in >> receiveMsg;

			if (_first)//��� ������ ���������?
			{
				rServer.AuthorizeConnection(clientGuid, receiveMsg);
				return;
			}
			else
			{
				//�������� ���������� �������
				rServer.HandleMessage(clientGuid, receiveMsg);
			}
		}

		ReadMessage();//���������� ������
	}

	void Connection::TimerHandler(const system::error_code & _error)
	{
		if (_error)
		{
			if (_error != asio::error::operation_aborted)
			{
				BOOST_LOG_TRIVIAL(error) << _error.message();
			}
		}

		//��������� ����������
		rServer.DeleteConnection(clientGuid);
	}
}
