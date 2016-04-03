#pragma once

#include "IMsgFabric.h"
#include "ShortEnums.h"
#include "AuthorizingParseSection.h"
#include "MessageParseSection.h"
#include "BaseParseSection.h"
#include "Settings.h"

namespace JsonParser
{

	class Parser
	{
	public:
		Parser();

		//������� ��������� �� jsValue ����������� �� fabricObject
		std::string CreateMessage(const IMsgFabric &fabricObjec);

		//������ string � jsValue � ��������� ������ ���������� ������(���������� ������-�������)
		ChatServer::OptionCommand ParseMessage(const std::string &guid, const std::string &message);

	private:

		//��������� ������ � jsValue(����������� true ��� ������� ��������, ����� false)
		bool IsLoad(const std::string &string);

		Json::Value jsValue;
		Json::Reader jsReader;//��� ������ �� string
		Json::FastWriter jsWriter;//��� ������ �� jsValue � string

		std::vector<std::unique_ptr<BaseParseSection>> sectionList;//������ ������ ��� ��������
	};
}