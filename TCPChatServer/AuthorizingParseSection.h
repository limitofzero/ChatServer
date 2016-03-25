#pragma once
#include "BaseParseSection.h"

namespace JsonParser
{

	class AuthorizingParseSection :
		public BaseParseSection
	{
	public:
		AuthorizingParseSection(const Json::Value &root, const Json::Value &schemaDoc) :
			BaseParseSection(root, schemaDoc)
		{}

		ChatServer::OptionCommand Parse() override;
	};
}

