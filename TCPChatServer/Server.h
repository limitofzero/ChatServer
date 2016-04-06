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
		void DeleteConnection(const std::string &guid, const bool authorized = false) override;

		//��������� ���������
		void HandleMessage(const std::string &guid, const std::string &message) override;

		//�����������
		void AuthorizeConnection(const std::string &tempGuid, const std::string &message) override;

		//���������� ����� ����������
		std::chrono::seconds GetDisconnectTime() const override
		{
			return disconnectTime;
		}

		//��������� IAcceptor

		//�������� ������� �����-������� �� ����� ��� �������� �����������
		void CreateConnection(SocketPtr &socket) override;

		//��������� ��� ���������� ������ �������

		//��������� ��������� �������������
		virtual void WriteMessage(const std::string &guid, const std::string &message) override;

		//�������� ���������� � ������ �����������
		virtual void AddAuthorizedConnection(const std::string &tempGuid, const std::string &newGuid) override;

	private:
		
		//��������������� ��������� �������� �����������
		void DisconnectFromList(ConnectionList &list, const std::string &guid);

		asio::io_service io_service;//��� ������ ������������ �-��
		Acceptor acceptor;//������� ����� �� ������� �����������
		JsonParser::Parser jsParser;//������ ��� ������� ���������(�/�� json ������)

		const std::chrono::seconds disconnectTime;//����� ���������� ���������� �� �������(� ��������)
		uint32_t connectionsCounter;//������� �����������
		
		ConnectionList newConnections;//������ ������������������ �����������(���� - ��������� ����)
		ConnectionList authorizedConnections;//������ ���������������� �����������(���� - ����(�����))
	};
}