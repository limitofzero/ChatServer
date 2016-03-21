#include "MessageParseSection.h"
#include "WriteMessage.h"

ChatServer::OptionCommand JsonParser::MessageParseSection::Parse()
{
	ChatServer::OptionCommand command;

	if (IsValid)//���� ��������� �������
	{
		//��������� ������
		const auto &root = jsValue["Message"];
		auto msgGuid = root["guid"].asString();
		auto content = root["content"].asString();

		//������� ������-��������
		Command::ICommand *command = new Command::WriteMessage(guid, );

		std::unique_ptr<Command::ICommand> commandPtr(new Command::WriteMessage(guid, content));
		return ChatServer::OptionCommand(std::move(commandPtr));//����������� � ��������
	}

	return command;//���� ��������� �� �������, ���������� ������ ��������	

}
