#pragma once

#include "ShortEnums.h"

namespace Command
{
	using namespace ChatServer;

	class Server;
	//��������� ��� ������ - ��������
	class ICommand
	{
		//��������� ��������
		virtual void Execute(Server &_server) = 0;
	};
}