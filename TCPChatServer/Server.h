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
		public ICommandInterface
	{
		using ConnectionList = std::unordered_map<std::string, std::shared_ptr<Connection>>;

	public:

		Server() :
			acceptor(*this, Settings::Instance().port),
			disconnectTime(Settings::Instance().secondsToDisconnect)
		{}

		void Start()
		{ 
			acceptor.Start();
			io_service.run();
		}

		~Server()
		{
			io_service.stop();
		}
		
		//���������� ������ �� io_service
		asio::io_service &GetIOService() override
		{
			return io_service;
		}

		//���������� ��������� ������������ ������������
		void WriteMessage(const std::string &guid, const std::string &message);

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
		void CreateConnection(asio::ip::tcp::socket socket) override;

		//��������� ��� ���������� ������ �������

		//��������� ��������� �������������
		virtual void WriteClientMessage(const std::string &message) override;

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