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

	//������� ����� ��� �������� ���������
	class BaseParseSection
	{
	public:
		BaseParseSection(const Json::Value &root, const Json::Value &schemaDoc);

		//���������� ������-��������, ���� ������� ����������(� ��������� ������ ���������� ������ ������)
		virtual ChatServer::OptionCommand Parse();


	protected:
		//���������, ������� �� ���������
		bool IsValid();

		const Json::Value &jsValue;//������ �� ������ ��� ��������

	private:
		Schema schema;
		SchemaParser valijsonParser;
		Validator validator;
		JsonCppAdapter schemaAdapter;
	};
}