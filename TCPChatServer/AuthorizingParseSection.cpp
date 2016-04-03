#include "AuthorizingParseSection.h"
#include "AuthorizeConnection.h"

ChatServer::OptionCommand JsonParser::AuthorizingParseSection::Parse(const std::string &guid)
{
	ChatServer::OptionCommand command;

	if (IsValid())//���� ��������� �������
	{
		//��������� ������
		const auto &root = jsValue["Authorizing"];
		auto msgGuid = root["guid"].asString();
		if (guid != msgGuid)//���� ����� �� ���������
		{
			return command;
		}

		auto password = root["password"].asString();

		//������� ������-��������
		return ChatServer::OptionCommand(
			std::make_unique<Command::AuthorizeConnection>(guid, msgGuid, password));//����������� � ��������
	}

	return command;//���� ��������� �� �������, ���������� ������ ��������
}
