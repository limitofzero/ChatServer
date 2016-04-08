#pragma once
#include "ICommand.h"

namespace Command
{
	//----------------����������
	class WriteMessage : public ICommand
	{
	public:
		WriteMessage(const std::string _guid, const std::string _message) :
			guidClient(_guid),
			msgFromClient(_message)
		{}

		// ������������ ����� ICommand
		virtual void Execute(ChatServer::ICommandInterface & _server) override
		{
			_server.WriteClientMessage(msgFromClient);
		}


	private:
		const std::string guidClient;
		const std::string msgFromClient;
	};
}