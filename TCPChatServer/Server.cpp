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
		if (authorized)//если клиент был авторизирован
		{
			//удаляем его из списка автор-х подключений
			DisconnectFromList(authorizedConnections, guid);
		}
		else
		{
			//удаляем из списка временных подключений
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
		//парсим сообщение и получаем объект-команду
		auto command = jsParser.ParseMessage(guid, message);
		if (command)//если объект не пустой
		{
			(*command)->Execute(*this);//выполняем команду
		}
		else
		{
			//если не удалось распарсить сообщение(отсылаем сообщение об ошибке парснига)
			JsonParser::ErrorMsgFabric error(SERVER_ERROR::PARSING);
			auto errorMessage = jsParser.CreateMessage(error);

			//отсылаем сообщение об ошибке
			WriteMessage(guid, errorMessage);
		}
	}

	void Server::AuthorizeConnection(const std::string &tempGuid, const std::string &message)
	{
		//обрабатываем подключение
		HandleMessage(tempGuid, message);
		DeleteConnection(tempGuid, false);//удаляем подключение из списка временных
	}

	void Server::CreateConnection(SocketPtr &socket)
	{
		//генерируем временный guid
		std::string tempGuid = "TMP_" + connectionsCounter;
		//создаем подключение и добавляем его в список неавторизированных
		newConnections.emplace(std::make_shared<Connection>(*this, socket, tempGuid));

		BOOST_LOG_TRIVIAL(info) << "Add new connection " << tempGuid;
	}

	void Server::WriteMessage(const std::string &guid, const std::string &message)
	{
		//отправляет сообщение пользователю guid
		if (authorizedConnections.find(guid) != authorizedConnections.end())
		{
			authorizedConnections.at(guid)->WriteMessage(message);
		}
	}

	void Server::AddAuthorizedConnection(const std::string &tempGuid, const std::string &newGuid)
	{
		//если подлкючение с данным гуид существует
		if (newConnections.find(tempGuid) != newConnections.end())
		{
			auto &connection = newConnections.at(tempGuid);
			authorizedConnections.emplace(std::move(connection));//переносим подлкючение в список проверенных
			authorizedConnections.at(tempGuid)->SetGuid(newGuid);//дописать
			
			BOOST_LOG_TRIVIAL(info) << "Add authorized connection " << newGuid;
			JsonParser::AuthorizeMsgFabric msg(true);
			auto strMessage = jsParser.CreateMessage(msg);
			WriteMessage(newGuid ,strMessage);
			
			//удаляем пустое соединеие
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
