#pragma once

#include "ServerInterface.h"
#include <boost/asio/system_timer.hpp>

namespace ChatServer
{

	using namespace boost;
	//�����, �������������� ������ � ������������(��������/����� ���������/����������)
	class Connection : std::enable_shared_from_this<Connection>
	{
	public:
		Connection(IConnection &_server, SocketPtr &_socket, const std::string _guid) :
			rServer(_server),
			pSocket(std::move(_socket)),
			disconnectTime(_server.GetDisconnectTime()),
			disconnectTimer(_server.GetIOService()),
			clientGuid(_guid)
		{}

		Connection(Connection &&_connection) :
			rServer(_connection.rServer),
			pSocket(std::move(_connection.pSocket)),
			disconnectTime(_connection.disconnectTime),
			disconnectTimer(rServer.GetIOService()),
			clientGuid(std::move(_connection.clientGuid))
		{}
		
		Connection(const IConnection &_connection) = delete;
		Connection &operator=(const IConnection &_connection) = delete;
		Connection &operator=(IConnection &&_connection) = delete;

		~Connection()
		{
			Disconnect();
		}

		//������ ������������� ������
		void ReadMessage(const bool _first = false);

		//�������� ��������� � �����
		void WriteMessage(const std::string &message);

		//������ ������� ����������
		void StartDisconnectTimer();

		//����� ������� ����������
		void ResetDisconnectTimer();

		//�������� ���� ������������
		void SetGuid(const std::string &newGuid)
		{
			clientGuid = newGuid;
			ResetDisconnectTimer();
		}

	private:
		//�������� ��� �������� � ��������� ������������ �����
		void Disconnect();

		//���������� ������
		void OnRead(const system::error_code &_error, const std::size_t _bytes, const bool _first);

		//���������� ������� �������
		void TimerHandler(const system::error_code &_error);

		IConnection &rServer;//������ �� ��������� �������
		SocketPtr pSocket;//��������� �� �����

		asio::streambuf writeBuffer;
		asio::streambuf readBuffer;

		asio::system_timer disconnectTimer;//������ ����������
		const std::chrono::seconds disconnectTime;//�����, ������ ������ ������ ����������� ������

		std::string clientGuid;//���� ������������(���)
		const char delimiter{ '\0' };//������ �� �������� ���� ������ ������ � ������
	};
}