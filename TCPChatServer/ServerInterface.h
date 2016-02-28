#pragma once


#include "ShortEnums.h"
#include <chrono>

namespace ChatServer
{
	class IConnection
	{
	public:
		//��������� �������
		virtual void DeleteConnection(const std::string &_guid) = 0;
		
		//���������� ������ �� io_service --------- �������� ������!!!!!!!!!!!!!!!!
		virtual boost::asio::io_service &GetIOService() = 0;

		//��������� ���������
		virtual void HandleMessage(const std::string &_guid, const std::string &_message) = 0;

		//�����������
		virtual void AuthorizeConnection(const std::string &_temp_guid, const std::string &_message) = 0;

		//���������� ����� ����������
		virtual std::chrono::seconds GetDisconnectTime() = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
	public:
		//���������� ������ �� io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//�������� ������� �����-������� �� ����� ��� �������� �����������
		virtual void CreateConnection(SocketPtr &_socket) = 0;

		virtual ~IAcceptor() = default;
	};
}
