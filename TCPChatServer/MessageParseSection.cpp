#include "MessageParseSection.h"
#include "WriteMessage.h"

ChatServer::OptionCommand JsonParser::MessageParseSection::Parse(const std::string &guid)
{
	ChatServer::OptionCommand command;

	if (IsValid())//если сообщение валидно
	{
		//извлекаем данные

		const auto &root = jsValue["Message"];

		auto msgGuid = root["guid"].asString();
		if (guid != msgGuid)//если пользовательский гуиды не совпадают
		{
			return command;
		}

		auto content = root["content"].asString();

		//создаем объект-комманду
		return ChatServer::OptionCommand(std::make_unique<Command::WriteMessage>(msgGuid, content));//упаковываем в опшионал
	}

	return command;//если сообщение не валидно, возвращаем пустой опшионал	
}
