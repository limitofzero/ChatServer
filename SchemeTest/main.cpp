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
#include <assert.h>

Json::Value loadDocument(const std::string &fileName, bool isFile = true)
{
	Json::Value jsValue;
	Json::Reader reader;

	if (isFile)
	{
		std::ifstream ifStream(fileName);

		if (!ifStream.is_open())
		{
			std::cout << "File didn't read!\n";
		}

		if (!reader.parse(ifStream, jsValue, true))
		{
			throw std::runtime_error("Unable to parse " + fileName);
		}
	}
	else
	{
		if (!reader.parse(fileName, jsValue, true))
		{
			throw std::runtime_error("Unable to parse " + fileName);
		}
	}

	return jsValue;
}

bool ReadAndValidateNode(const std::string &fileName, const std::string &schemeFileName, bool isFile = true)
{
	using valijson::Schema;
	using valijson::SchemaParser;
	using valijson::Validator;
	using valijson::ValidationResults;
	using valijson::adapters::JsonCppAdapter;


	Json::Value root, scheme;
	try
	{
		root = loadDocument(fileName, isFile);
		scheme = loadDocument(schemeFileName, isFile);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << "\n";
		return false;
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
		return false;
	}

	Validator validator;
	ValidationResults results;
	
	if (validator.validate(schema, docAdapter, &results))
	{
		return true;
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

		return false;
	}
}



int main()
{
	assert(ReadAndValidateNode("Authorizing.txt", JsonParser::authorizedScheme, false) == true);
	std::cout <<  + "Authorizing.txt is valid\n";

	assert(ReadAndValidateNode("Message.txt", JsonParser::messageScheme, false) == true);
	std::cout << +"Message.txt is valid\n";
	
	system("pause");
	return 0;
}
