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
	public:
		BaseParseSection(const Json::Value &root, const Json::Value &schemaDoc);

		//возвращает объект-комманду, если удалось распарсить(в противном случае возвращает пустой объект)
		virtual ChatServer::OptionCommand Parse(const std::string &guid) = 0;


	protected:
		//проверяет, валидно ли сообщение
		bool IsValid();

		const Json::Value &jsValue;//ссылка на секцию для парсинга

	private:
		Schema schema;
		SchemaParser valijsonParser;
		Validator validator;
		JsonCppAdapter schemaAdapter;
	};
}