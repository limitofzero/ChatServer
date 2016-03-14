#pragma once

#include "IMsgFabric.h"
#include "ShortEnums.h"

namespace JsonParser
{
	class Parser
	{
	public:
		Parser()
		{
		}

		//������� ��������� �� jsValue ����������� �� fabricObject
		std::string CreateMessage(const IMsgFabric &fabricObjec);

		//������ string � jsValue � ��������� ������ ���������� ������(���������� ������-�������)
		ChatServer::OptionCommand ParseMessage(const std::string &guid, const std::string &message);

	private:
		bool IsLoad(const std::string &string);//��������� ������ � jsValue(����������� true ��� ������� ��������, ����� false)

		Json::Value jsValue;
		Json::Reader jsReader;//��� ������ �� string
		Json::FastWriter jsWriter;//��� ������ �� jsValue � string
	};
}