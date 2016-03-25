#include "AuthorizingParseSection.h"
#include "AuthorizeConnection.h"

ChatServer::OptionCommand JsonParser::AuthorizingParseSection::Parse()
{
	ChatServer::OptionCommand command;

	if (IsValid())//если сообщение валидно
	{
		//извлекаем данные
		const auto &root = jsValue["Authorizing"];
		auto msgGuid = root["guid"].asString();
		auto password = root["password"].asString();

		//создаем объект-комманду
		Command::ICommand *command = new Command::AuthorizeConnection(guid, msgGuid, password);

		std::unique_ptr<Command::ICommand> commandPtr(new Command::AuthorizeConnection(guid, msgGuid, password));
		return ChatServer::OptionCommand(std::move(commandPtr));//упаковываем в опшионал
	}

	return command;//если сообщение не валидно, возвращаем пустой опшионал
}
