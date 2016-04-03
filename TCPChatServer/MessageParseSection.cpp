#include "MessageParseSection.h"
#include "WriteMessage.h"

ChatServer::OptionCommand JsonParser::MessageParseSection::Parse(const std::string &guid)
{
	ChatServer::OptionCommand command;

	if (IsValid())//���� ��������� �������
	{
		//��������� ������

		const auto &root = jsValue["Message"];
		auto msgGuid = root["guid"].asString();
		if (guid != msgGuid)//���� ���������������� ����� �� ���������
		{
			return command;
		}

		auto content = root["content"].asString();

		//������� ������-��������
		return ChatServer::OptionCommand(std::make_unique<Command::WriteMessage>(msgGuid, content));//����������� � ��������
	}

	return command;//���� ��������� �� �������, ���������� ������ ��������	
}
