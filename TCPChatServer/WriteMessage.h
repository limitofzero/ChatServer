#pragma once
#include "ICommand.h"

namespace Command
{
	class WriteMessage : public ICommand
	{
		WriteMessage(const std::string _guid, const std::string _message) :
			guidClient(_guid),
			msgFromClient(_message)
		{}

		// ”наследовано через ICommand
		virtual void Execute(ChatServer::ICommand & _server) override
		{
			_server.WriteMessage(guidClient, msgFromClient);//код дл€ написани€ сообщени€
		}


	private:
		const std::string guidClient;
		const std::string msgFromClient;
	};
}