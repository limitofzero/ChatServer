#include "Parser.h"
#include <boost/log/trivial.hpp>
#include "JsSchemes.h"

JsonParser::Parser::Parser()
{
	Json::Value msgSchemeValue, authorizedSchemeValue;
	auto checkFirst = jsReader.parse(messageScheme, msgSchemeValue, false);
	auto checkSecond = jsReader.parse(authorizedScheme, authorizedSchemeValue, false);
	if (!(checkFirst && checkSecond))//если не удалось правильно распарсить схемы
	{
		throw std::runtime_error("Uncorrect scheme");//генерируем исключение
	}

	//инициализируем секции
	sectionList.emplace_back(std::make_unique<AuthorizingParseSection>(jsValue, authorizedSchemeValue));
	sectionList.emplace_back(std::make_unique<MessageParseSection>(jsValue, messageScheme));
}

std::string JsonParser::Parser::CreateMessage(const IMsgFabric &fabricObjec)
{
	auto jsValue = fabricObjec.CreateJsValue();
	return jsWriter.write(jsValue);//записываем json параметры в строку
}

ChatServer::OptionCommand JsonParser::Parser::ParseMessage(const std::string &guid, const std::string &message)
{
	if (!IsLoad(message))//если не удалось загрузить сообщение
	{
		BOOST_LOG_TRIVIAL(error) << "Incorrect message(" << message << ")";
		return ChatServer::OptionCommand();
	}

	for (auto &iter : sectionList)
	{
		//парсим, пока не получим инициализированный объект-команду
		auto commandObject = iter
		if (commandObject)
			return commandObject;
	}

	//в случае, если не удалось распарсить, возвращаем пустой объект
	BOOST_LOG_TRIVIAL(error) << "Parsing error(" << message << ")";
	return ChatServer::OptionCommand();
}

bool JsonParser::Parser::IsLoad(const std::string &string)
{
	//очищаем ноду перед парсингом
	jsValue.clear();
	//возвращает true при удачном парсинге строки
	return jsReader.parse(string, jsValue);
}


