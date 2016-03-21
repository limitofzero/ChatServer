#pragma once

#include "IMsgFabric.h"
#include "ShortEnums.h"

namespace JsonParser
{
	class BaseParserSection;

	class Parser
	{
	public:
		Parser()
		{
			//код для инициализации секций

			//-----------------------------
		}

		//создает сообщение из jsValue полученного из fabricObject
		std::string CreateMessage(const IMsgFabric &fabricObjec);

		//парсит string в jsValue и выполняет анализ полученных данных(возвращает объект-команду)
		ChatServer::OptionCommand ParseMessage(const std::string &guid, const std::string &message);

	private:
		bool IsLoad(const std::string &string);//загружает данные в jsValue(возвраящает true при удачной загрузке, иначе false)

		Json::Value jsValue;
		Json::Reader jsReader;//для чтения из string
		Json::FastWriter jsWriter;//для записи из jsValue в string

		std::vector<std::unique_ptr<BaseParserSection>> sections;//список секций для парсинга
	};
}