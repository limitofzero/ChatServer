#pragma once
#include "ServerInterface.h"
#include "Connection.h"
#include "Acceptor.h"
#include "Settings.h"
#include "Parser.h"
#include <unordered_map>


namespace ChatServer
{
	using namespace boost;

	//�����, ����������� �-�� �������
	class Server : 
		public IConnection, 
		public IAcceptor, 
		public ICommand
	{
		using ConnectionList = std::unordered_map<std::string, std::shared_ptr<Connection>>;

	public:
		Server();
		
		//���������� ������ �� io_service
		asio::io_service &GetIOService() override
		{
			return io_service;
		}

		//��������� IConnection

		//��������� ������� � ������� ��� �� ������ �����������
		void DeleteConnection(const std::string &_guid) override;

		//��������� ���������
		void HandleMessage(const std::string &_guid, const std::string &_message) override;

		//�����������
		void AuthorizeConnection(const std::string &_temp_guid, const std::string &_message) override;

		//���������� ����� ����������
		std::chrono::seconds GetDisconnectTime() override;



	private:
		asio::io_service io_service;//��� ������ ������������ �-��
		Acceptor acceptor;//������� ����� �� ������� �����������
		JsonParser::Parser jsParser;//������ ��� ������� ���������(�/�� json ������)

		const std::chrono::seconds disconnectTime;//����� ���������� ���������� �� �������(� ��������)
		
		ConnectionList newConnections;//������ ������������������ �����������(���� - ��������� ����)
		ConnectionList authorizedConnections;//������ ���������������� �����������(���� - ����(�����))
	};
}