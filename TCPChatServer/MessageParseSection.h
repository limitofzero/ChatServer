#pragma once

#include "BaseParseSection.h"

namespace JsonParser
{
	class MessageParseSection : public BaseParseSection
	{
	public:
		MessageParseSection(const Json::Value &root, const Json::Value &schemaDoc, const std::string &clientGuid) :
			BaseParseSection(root, schemaDoc, clientGuid)
			{}

		ChatServer::OptionCommand Parse() override;
	};
}