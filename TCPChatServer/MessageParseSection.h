#pragma once

#include "BaseParseSection.h"
#include <boost\log\trivial.hpp>

namespace JsonParser
{
	class MessageParseSection : public BaseParseSection
	{
	public:
		MessageParseSection(const Json::Value &root, const Json::Value &schemaDoc) :
			BaseParseSection(root, schemaDoc)
			{}

		ChatServer::OptionCommand Parse(const std::string &guid) override;
	};
}