#include "Parser.h"
#include <boost/log/trivial.hpp>
#include "JsSchemes.h"

JsonParser::Parser::Parser()
{
	Json::Value msgSchemeValue, authorizedSchemeValue;
	auto checkFirst = jsReader.parse(messageScheme, msgSchemeValue, false);
	auto checkSecond = jsReader.parse(authorizedScheme, authorizedSchemeValue, false);
	if (!(checkFirst && checkSecond))//���� �� ������� ��������� ���������� �����
	{
		throw std::runtime_error("Uncorrect scheme");//���������� ����������
	}

	//�������������� ������
	auto section = std::make_unique<BaseParserSection>(new AuthorizingParseSection(jsValue, authorizedSchemeValue, ""));
	sectionList.push_back(std::move(section));

	section = std::make_unique<BaseParserSection>(new MessageParseSection(jsValue, messageScheme, ""));
	sectionList.push_back(std::move(section));
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

	for (const auto &iter : sectionList)
	{
		//������, ���� �� ������� ������������������ ������-�������
		auto commandObject = iter->Parse(message, guid);
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


