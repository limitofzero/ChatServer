#pragma once
#include "ICommand.h"

namespace Command
{
	class WriteMessage : public ICommand
	{
	public:
		WriteMessage(const std::string _guid, const std::string _message) :
			guidClient(_guid),
			msgFromClient(_message)
		{}

		// ”наследовано через ICommand
		virtual void Execute(ChatServer::ICommand & _server) override
		{
#if 0
			_server.WriteMessage(guidClient, msgFromClient);//код дл€ написани€ сообщени€
#endif
		}


	private:
		const std::string guidClient;
		const std::string msgFromClient;
	};
}