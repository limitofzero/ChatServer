#include "AuthorizeConnection.h"

void Command::AuthorizeConnection::Execute(ChatServer::ICommand & _server)
{
	_server.AddAuthorizedConnection(tempGuid, clientGuid);
}
