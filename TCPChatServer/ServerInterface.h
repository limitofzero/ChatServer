#pragma once


#include "ShortEnums.h"
#include <chrono>

namespace ChatServer
{
	class IConnection
	{
	public:
		//��������� �������
		virtual void DeleteConnection(const std::string &guid, const bool authorized = false) = 0;
		
		//���������� ������ �� io_service --------- �������� ������!!!!!!!!!!!!!!!!
		virtual boost::asio::io_service &GetIOService() = 0;

		//��������� ���������
		virtual void HandleMessage(const std::string &guid, const std::string &message) = 0;

		//�����������
		virtual void AuthorizeConnection(const std::string &tempGuid, const std::string &message) = 0;

		//���������� ����� ����������
		virtual std::chrono::seconds GetDisconnectTime() const = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
	public:
		//���������� ������ �� io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//�������� ������� �����-������� �� ����� ��� �������� �����������
		virtual void CreateConnection(SocketPtr &socket) = 0;

		virtual ~IAcceptor() = default;
	};

	//��������� ��� ���������� ������ �������
	class ICommandInterface
	{
	public:
		//��������� ��������� �������������
		virtual void WriteClientMessage(const std::string &message) = 0;

		//�������� ���������� � ������ �����������
		virtual void AddAuthorizedConnection(const std::string &tempGuid, const std::string &newGuid) = 0;

		virtual ~ICommandInterface() = default;
	};
}
