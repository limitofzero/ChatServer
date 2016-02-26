#pragma once

#include <boost/asio.hpp>
#include <memory>

namespace ChatServer
{
	using Socket = boost::asio::ip::tcp::socket;
	using SocketPtr = std::shared_ptr<Socket>;

	class IConnection
	{
	public:
		//��������� �������
		virtual void DeleteConnection(const std::string &_clientGuid) = 0;
		
		//���������� ������ �� io_service --------- �������� ������!!!!!!!!!!!!!!!!
		virtual boost::asio::io_service &GetIOService() = 0;

		//��������� ���������
		virtual void HandleMessage(const std::string &_clientGuid, const std::string &_clientMsg) = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
	public:
		//���������� ������ �� io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//�������� ������� �����-������� �� ����� ��� �������� �����������
		virtual void CreateConnection(SocketPtr &_pSocket) = 0;

		virtual ~IAcceptor() = default;
	};


	class IAuthorizator
	{
	public:
		//��������� ���������� ����������� ������������ �� ������
		virtual void AddConnection(const std::string &newGuid) = 0�

		virtual ~IAuthorizator() = default;
	};
}
