#pragma once

#include "BaseParseSection.h"

namespace JsonParser
{
	class MessageParseSection : public BaseParseSection
	{
	public:
		MessageParseSection(const Json::Value &root, const Json::Value &schemaDoc) :
			BaseParseSection(root, schemaDoc)
			{}

		ChatServer::OptionCommand Parse() override;
	};
}