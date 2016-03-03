#pragma once

#include "ServerInterface.h"
#include "ShortEnums.h"

namespace Command
{
	using namespace ChatServer;

	class Server;
	//��������� ��� ������ - ��������
	class ICommand
	{
		//��������� ��������
		virtual void Execute(ChatServer::ICommand &_server) = 0;
	};
}