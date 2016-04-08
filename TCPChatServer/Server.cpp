#include "Server.h"
#include "ICommand.h"
#include "Enums.h"
#include "ErrorMsgFabric.h"
#include "AcceptMsgFabric.h"
#include "AuthorizeMsgFabric.h"

namespace ChatServer
{
	void Server::DeleteConnection(const std::string &guid, const bool authorized)
	{
		if (authorized)//���� ������ ��� �������������
		{
			//������� ��� �� ������ �����-� �����������
			DisconnectFromList(authorizedConnections, guid);
		}
		else
		{
			//������� �� ������ ��������� �����������
			DisconnectFromList(newConnections, guid);
		}
	}

	void Server::DisconnectFromList(Server::ConnectionList &list, const std::string &guid)
	{
		if (list.find(guid) != list.end())
		{
			list.erase(guid);
			BOOST_LOG_TRIVIAL(info) << "Disconnect " << guid;
		}

		BOOST_LOG_TRIVIAL(error) << "Connection don't exist";
	}

	void Server::HandleMessage(const std::string &guid, const std::string &message)
	{
		//������ ��������� � �������� ������-�������
		auto command = jsParser.ParseMessage(guid, message);
		if (command)//���� ������ �� ������
		{
			(*command)->Execute(*this);//��������� �������
		}
		else
		{
			//���� �� ������� ���������� ���������(�������� ��������� �� ������ ��������)
			JsonParser::ErrorMsgFabric error(SERVER_ERROR::PARSING);
			auto errorMessage = jsParser.CreateMessage(error);

			//�������� ��������� �� ������
			WriteMessage(guid, errorMessage);
		}
	}

	void Server::AuthorizeConnection(const std::string &tempGuid, const std::string &message)
	{
		//������������ �����������
		HandleMessage(tempGuid, message);
		DeleteConnection(tempGuid, false);//������� ����������� �� ������ ���������
	}

	void Server::CreateConnection(asio::ip::tcp::socket socket)
	{
		//���������� ��������� guid
		++connectionsCounter;
		std::string tempGuid = "TMP_" + std::to_string(connectionsCounter);
		//������� ����������� � ��������� ��� � ������ ������������������
		newConnections.emplace(tempGuid, std::make_shared<Connection>(*this, std::move(socket), tempGuid));

		BOOST_LOG_TRIVIAL(info) << "Add new connection " << tempGuid;
	}

	void Server::WriteMessage(const std::string &guid, const std::string &message)
	{
		//���������� ��������� ������������ guid
		if (authorizedConnections.find(guid) != authorizedConnections.end())
		{
			authorizedConnections.at(guid)->WriteMessage(message);
		}
	}

	void Server::AddAuthorizedConnection(const std::string &tempGuid, const std::string &newGuid)
	{
		//���� ����������� � ������ ���� ����������
		if (newConnections.find(tempGuid) != newConnections.end())
		{
			auto &connection = newConnections.at(tempGuid);
			authorizedConnections.emplace(newGuid, std::move(connection));//��������� ����������� � ������ �����������
			authorizedConnections.at(tempGuid)->SetGuid(newGuid);//��������
			
			BOOST_LOG_TRIVIAL(info) << "Add authorized connection " << newGuid;
			JsonParser::AuthorizeMsgFabric msg(true);
			auto strMessage = jsParser.CreateMessage(msg);
			WriteMessage(newGuid ,strMessage);
			
			//������� ������ ���������
			newConnections.erase(tempGuid);
		}

		BOOST_LOG_TRIVIAL(error) << "Connection don't exist";
	}

	void Server::WriteClientMessage(const std::string &message)
	{
		for (auto &i : authorizedConnections)
		{
			i.second->WriteMessage(message);
		}
	}
}
