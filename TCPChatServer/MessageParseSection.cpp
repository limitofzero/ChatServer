#include "MessageParseSection.h"
#include "WriteMessage.h"

ChatServer::OptionCommand JsonParser::MessageParseSection::Parse()
{
	ChatServer::OptionCommand command;

	if (IsValid)//если сообщение валидно
	{
		//извлекаем данные
		const auto &root = jsValue["Message"];
		auto msgGuid = root["guid"].asString();
		auto content = root["content"].asString();

		//создаем объект-комманду
		Command::ICommand *command = new Command::WriteMessage(guid, );

		std::unique_ptr<Command::ICommand> commandPtr(new Command::WriteMessage(guid, content));
		return ChatServer::OptionCommand(std::move(commandPtr));//упаковываем в опшионал
	}

	return command;//если сообщение не валидно, возвращаем пустой опшионал	

}
