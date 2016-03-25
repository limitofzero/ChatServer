#include "MessageParseSection.h"
#include "WriteMessage.h"

ChatServer::OptionCommand JsonParser::MessageParseSection::Parse()
{
	ChatServer::OptionCommand command;

	if (IsValid())//���� ��������� �������
	{
		//��������� ������
		const auto &root = jsValue["Message"];
		auto msgGuid = root["guid"].asString();
		auto content = root["content"].asString();

		//������� ������-��������

		std::unique_ptr<Command::ICommand> commandPtr(new Command::WriteMessage(msgGuid, content));
		return ChatServer::OptionCommand(std::move(commandPtr));//����������� � ��������
	}

	return command;//���� ��������� �� �������, ���������� ������ ��������	

}
