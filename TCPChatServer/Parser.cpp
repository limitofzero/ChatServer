#include "Parser.h"

std::string JsonParser::Parser::CreateMessage(const IMsgFabric &fabricObjec)
{
	auto jsValue = fabricObjec.CreateJsValue();
	return jsWriter.write(jsValue);//записываем json параметры в строку
}

bool JsonParser::Parser::IsLoad(const std::string &string)
{
	//очищаем ноду перед парсингом
	jsValue.clear();
	//возвращает true при удачном парсинге строки
	return jsReader.parse(string, jsValue);
}


