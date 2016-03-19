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
		std::cout << "File didn't read!\n";
	}

	if (!reader.parse(ifStream, jsValue, true))
	{
		throw std::runtime_error("Unable to parse " + fileName);
	}

	return jsValue;
}

void ReadAndValidateNode(const std::string &fileName, const std::string &schemeFileName)
{
	using valijson::Schema;
	using valijson::SchemaParser;
	using valijson::Validator;
	using valijson::ValidationResults;
	using valijson::adapters::JsonCppAdapter;


	Json::Value root, scheme;
	try
	{
		root = loadDocument(fileName);
		scheme = loadDocument(schemeFileName);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << "\n";
		return;
	}
	
	JsonCppAdapter docAdapter(root);
	JsonCppAdapter schemaDocAdapter(scheme);
	
	
	SchemaParser parser(valijson::SchemaParser::kDraft4);
	Schema schema;
	try
	{
		parser.populateSchema(schemaDocAdapter, schema);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << "\n";
		return;
	}

	Validator validator;
	ValidationResults results;
	
	if (validator.validate(schema, docAdapter, &results))
	{
		std::cout << fileName + " is valid(" << schemeFileName << ")\n";
	}
	else
	{
		std::cout << fileName + " isn't valid(" << schemeFileName << ")\n";
		ValidationResults::Error error;
		uint8_t errorNum = 1;
		while (results.popError(error)) 
		{

			std::string context;
			auto itr = error.context.begin();
			for (; itr != error.context.end(); itr++) {
				context += *itr;
			}

			std::cout << "Error #" << errorNum << std::endl
				<< "  context: " << context << "\n"
				<< "  desc:    " << error.description << "\n";
			++errorNum;
		}
	}
}



int main()
{

	ReadAndValidateNode("Authorizing.txt", "../schema/authorizing.json");
	ReadAndValidateNode("Message.txt", "../schema/message.json");
	
	system("pause");
	return 0;
}
