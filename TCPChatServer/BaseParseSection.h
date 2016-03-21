#pragma once

#include <json/json.h>
#include <valijson\adapters\jsoncpp_adapter.hpp>
#include <valijson/schema.hpp>
#include <valijson/validator.hpp>
#include <valijson\schema_parser.hpp>
#include <valijson\validation_results.hpp>
#include "ShortEnums.h"


namespace JsonParser
{
	using valijson::Schema;
	using valijson::SchemaParser;
	using valijson::Validator;
	using valijson::ValidationResults;
	using valijson::adapters::JsonCppAdapter;

	//базовый класс для парсинга сообщений
	class BaseParseSection
	{
		BaseParseSection(const Json::Value &root, const Json::Value &schemaDoc, const std::string &clientGuid);

		//возвращает объект-комманду, если удалось распарсить(в противном случае возвращает пустой объект)
		virtual ChatServer::OptionCommand Parse();


	protected:
		//проверяет, валидно ли сообщение
		bool IsValid();

		const Json::Value &jsValue;//ссылка на секцию для парсинга
		const std::string &guid;//ссылка на гуди пользователя, сообещние которого нужно парсить

	private:
		Schema schema;
		SchemaParser valijsonParser;
		Validator validator;
		JsonCppAdapter schemaAdapter;
	};
}