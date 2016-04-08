#pragma once

#include "ServerInterface.h"
#include <boost/asio/system_timer.hpp>

using namespace boost;

namespace ChatServer
{
	//�����, �������������� ������ � ������������(��������/����� ���������/����������)
	class Connection : public std::enable_shared_from_this<Connection>
	{
	public:
		Connection(IConnection &_server, asio::ip::tcp::socket socket, const std::string _guid) :
			rServer(_server),
			socket(std::move(socket)),
			disconnectTime(_server.GetDisconnectTime()),
			disconnectTimer(_server.GetIOService()),
			clientGuid(_guid)
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
#if 0
			ResetDisconnectTimer();
#endif
			disconnectTimer.cancel();//��������� ������
		}

	private:
		//�������� ��� �������� � ��������� ������������ �����
		void Disconnect();

		//���������� ������
		void OnRead(const system::error_code &_error, const std::size_t _bytes, const bool _first);

		//���������� ������� �������
		void TimerHandler(const system::error_code &_error);

		IConnection &rServer;//������ �� ��������� �������
		asio::ip::tcp::socket socket;//��������� �� �����

		asio::streambuf writeBuffer;
		asio::streambuf readBuffer;

		asio::system_timer disconnectTimer;//������ ����������
		const std::chrono::seconds disconnectTime;//�����, ������ ������ ������ ����������� ������

		std::string clientGuid;//���� ������������(���)
		const char delimiter{ '\0' };//������ �� �������� ���� ������ ������ � ������
	};
}