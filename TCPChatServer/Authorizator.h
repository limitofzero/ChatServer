#pragma once

#include "ServerInterface.h"
#include <unordered_map>
#include <chrono>
#include <boost/asio/basic_deadline_timer.hpp>

namespace ChatServer
{
	using namespace boost;

	class BaseParser;
	//�����, �������������� �����������
	class Authorizator
	{
		using BufferPtr = std::shared_ptr<asio::streambuf>;

	public:
		Authorizator(IAuthorizator &_server, const uint16_t _disconnect_seconds) :
			rServer(_server),
			rService(_server.GetIOService()),
			disconnectSeconds(_disconnect_seconds)
			//��� ������������� �������
		{}

		//�������� �����������
		void WaitAuthorizedMessage(SocketPtr &_socket);

	private:
		//���������� ������
		void OnRead(const system::error_code &_error ,SocketPtr _socket, BufferPtr _buffer);

		//���������� ����������
		void TimeOut(SocketPtr _socket);

		IAuthorizator &rServer;//������ �� ������
		asio::io_service &rService;//������ �� io_services
		std::unique_ptr<BaseParser> pParser;//������
		const std::chrono::seconds disconnectSeconds;//����� ����������(��� �������)
	};
}