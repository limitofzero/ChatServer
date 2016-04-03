#include "Parser.h"
#include "JsSchemes.h"
#include <boost/log/trivial.hpp>

JsonParser::Parser::Parser()
{
	//�������� ������ �� ������
	auto &configs = ChatServer::Settings::Instance();

	Json::Value msgSchemeValue, authorizedSchemeValue;
	msgSchemeValue = configs.shemes.at("Message");
	authorizedSchemeValue = configs.shemes.at("Authorizing");

	//�������������� ������
	sectionList.emplace_back(std::make_unique<AuthorizingParseSection>(jsValue, authorizedSchemeValue));
	sectionList.emplace_back(std::make_unique<MessageParseSection>(jsValue, messageScheme));
}

std::string JsonParser::Parser::CreateMessage(const IMsgFabric &fabricObjec)
{
	auto jsValue = fabricObjec.CreateJsValue();
	return jsWriter.write(jsValue);//���������� json ��������� � ������
}

ChatServer::OptionCommand JsonParser::Parser::ParseMessage(const std::string &guid, const std::string &message)
{
	if (!IsLoad(message))//���� �� ������� ��������� ���������
	{
		BOOST_LOG_TRIVIAL(error) << "Incorrect message(" << message << ")";
		return ChatServer::OptionCommand();
	}

	for (auto &iter : sectionList)
	{
		//������, ���� �� ������� ������������������ ������-�������
		auto commandObject = iter->Parse(guid);
		if (commandObject)
			return commandObject;
	}

	//� ������, ���� �� ������� ����������, ���������� ������ ������
	BOOST_LOG_TRIVIAL(error) << "Parsing error(" << message << ")";
	return ChatServer::OptionCommand();
}

bool JsonParser::Parser::IsLoad(const std::string &string)
{
	//������� ���� ����� ���������
	jsValue.clear();
	//���������� true ��� ������� �������� ������
	return jsReader.parse(string, jsValue);
}


