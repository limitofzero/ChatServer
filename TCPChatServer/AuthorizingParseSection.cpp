#include "AuthorizingParseSection.h"
#include "AuthorizeConnection.h"

ChatServer::OptionCommand JsonParser::AuthorizingParseSection::Parse(const std::string &guid)
{
	ChatServer::OptionCommand command;

	if (IsValid())//если сообщение валидно
	{
		//извлекаем данные
		const auto &root = jsValue["Authorizing"];
		auto msgGuid = root["guid"].asString();
		if (guid != msgGuid)//если гуиды не совпадают
		{
			return command;
		}

		auto password = root["password"].asString();

		//создаем объект-комманду
		return ChatServer::OptionCommand(
			std::make_unique<Command::AuthorizeConnection>(guid, msgGuid, password));//упаковываем в опшионал
	}

	return command;//если сообщение не валидно, возвращаем пустой опшионал
}
