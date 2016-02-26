#pragma once

#include "ServerInterface.h"

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
			clientGuid(_guid)
		{}

		//������ ������������� ������
		void ReadMessage();

		//�������� ��������� � �����
		void WriteMessage(const std::string &message);

		//�������� ��� �������� � ��������� ������������ �����
		void Disconnect();

	private:
		//���������� ������
		void OnRead(const system::error_code &_error, const std::size_t _bytes);

		IConnection &rServer;//������ �� ��������� �������
		SocketPtr pSocket;//��������� �� �����

		asio::streambuf writeBuffer;
		asio::streambuf readBuffer;

		const std::string clientGuid;//���� ������������(���)
		const char delimiter{ '\0' };//������ �� �������� ���� ������ ������ � ������
	};
}