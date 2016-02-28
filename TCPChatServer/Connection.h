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

		//������ ������������� ������
		void ReadMessage(const bool _first = false);

		//�������� ��������� � �����
		void WriteMessage(const std::string &message);

		//�������� ��� �������� � ��������� ������������ �����
		void Disconnect();

		//������ ������� ����������
		void StartDisconnectTimer();

		//����� ������� ����������
		void ResetDisconnectTimer();

	private:
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

		const std::string clientGuid;//���� ������������(���)
		const char delimiter{ '\0' };//������ �� �������� ���� ������ ������ � ������
	};
}