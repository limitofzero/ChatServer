#include "Parser.h"
#include "JsSchemes.h"
#include <boost/log/trivial.hpp>

JsonParser::Parser::Parser()
{
	Json::Value msgSchemeValue, authorizedSchemeValue;
	auto checkFirst = jsReader.parse(messageScheme, msgSchemeValue, false);
	auto checkSecond = jsReader.parse(authorizedScheme, authorizedSchemeValue, false);

	if (!checkFirst)
	{
		throw std::runtime_error("Uncorrect scheme" + messageScheme);//���������� ����������
	}

	if (!checkSecond)
	{
		throw std::runtime_error("Uncorrect scheme" + authorizedScheme);//���������� ����������
	}

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


