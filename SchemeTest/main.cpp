#include <valijson\schema.hpp>
#include <json\json.h>
#include <valijson\adapters\jsoncpp_adapter.hpp>
#include <valijson\schema_parser.hpp>
#include <valijson\validation_results.hpp>
#include <valijson/validator.hpp>
#include <valijson/utils/jsoncpp_utils.hpp>
#include <fstream>
#include "../TCPChatServer/JsSchemes.h"
#include <iostream>

Json::Value loadDocument(const std::string &fileName)
{
	Json::Value jsValue;
	Json::Reader reader;
	std::ifstream ifStream(fileName);

	if (!ifStream.is_open())
	{
		std::cout << "Errror\n";
	}

	if (!reader.parse(ifStream, jsValue, true))
		throw std::runtime_error("Unable to parse " + fileName);
	return jsValue;
}

void ReadAndValidateNode(const std::string &fileName, const std::string &schemeFileName)
{
	using valijson::Schema;
	using valijson::SchemaParser;
	using valijson::Validator;
	using valijson::ValidationResults;
	using valijson::adapters::JsonCppAdapter;

	auto root = loadDocument(fileName);
	auto scheme = loadDocument(schemeFileName);
	
	JsonCppAdapter doc(root);
	JsonCppAdapter schemaDoc(scheme);
	
	SchemaParser parser(valijson::SchemaParser::kDraft4);
	Schema schema;
	parser.populateSchema(schemaDoc, schema);

	Validator validator;
	ValidationResults results;
	
	if (validator.validate(schema, doc, &results))
	{
		std::cout << fileName + " is valid(" << schemeFileName << ")\n";
	}
	else
	{
		std::cout << fileName + " isn't valid(" << schemeFileName << ")\n";
	}
}



int main()
{

	ReadAndValidateNode("Authorizing.txt", "../schema/authorizing.json");
	
	system("pause");
	return 0;
}
