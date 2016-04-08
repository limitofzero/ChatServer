#pragma once

#include "ServerInterface.h"



namespace Command
{
	//��������� ��� ������ - ��������
	class ICommand
	{
	public:
		//��������� ��������
		virtual void Execute(ChatServer::ICommandInterface &_server) = 0;
	};
}