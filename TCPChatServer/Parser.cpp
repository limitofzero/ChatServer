#include "Parser.h"
#include "JsSchemes.h"
#include <boost/log/trivial.hpp>

JsonParser::Parser::Parser()
{
	//получаем ссылку на конфиг
	auto &configs = ChatServer::Settings::Instance();

	Json::Value msgSchemeValue, authorizingSchemeValue;
	msgSchemeValue = configs.shemes.at("message");
	authorizingSchemeValue = configs.shemes.at("authorizing");

	//инициализируем секции
	sectionList.emplace_back(std::make_unique<AuthorizingParseSection>(jsValue, authorizingSchemeValue));
	sectionList.emplace_back(std::make_unique<MessageParseSection>(jsValue, msgSchemeValue));
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
		auto commandObject = iter->Parse(guid);
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


