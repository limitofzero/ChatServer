#include "BaseParseSection.h"
#include <boost/log/trivial.hpp>

JsonParser::BaseParseSection::BaseParseSection(
	const Json::Value & root, const Json::Value & schemaDoc, const std::string & clientGuid) :
	jsValue(root),
	guid(clientGuid),
	valijsonParser(SchemaParser::kDraft4),
	schemaAdapter(schemaDoc)
{
	try
	{
		valijsonParser.populateSchema(schemaAdapter, schema);
	}
	catch (std::runtime_error e)
	{
		BOOST_LOG_TRIVIAL(fatal) << e.what();
	}
}

bool JsonParser::BaseParseSection::IsValid()
{
	JsonCppAdapter docAdapter(jsValue);
	ValidationResults validResults;
	//возвращает true, если сообщение прошло валидацию
	return validator.validate(schema, docAdapter, &validResults);
}
