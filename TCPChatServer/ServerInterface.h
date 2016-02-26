#pragma once

#include <boost/asio.hpp>
#include <memory>

namespace Network
{
	using Socket = boost::asio::ip::tcp::socket;

	class IConnection
	{
		//��������� �������
		virtual void DeleteConnection(const std::string &_clientGuid) = 0;
		
		//���������� ������ �� io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//��������� ���������
		virtual void HandleMessage(const std::string &_clientGuid, const std::string &_clientMsg) = 0;

		virtual ~IConnection() = default;
	};

	class IAcceptor
	{
		//���������� ������ �� io_service
		virtual boost::asio::io_service &GetIOService() = 0;

		//�������� ������� �����-������� �� ����� ��� �������� �����������
		virtual void CreateConnection(std::shared_ptr<Socket> &pSocket) = 0;

		virtual ~IAcceptor() = default;
	};
}
