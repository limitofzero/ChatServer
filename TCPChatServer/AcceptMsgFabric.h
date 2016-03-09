#pragma once

#include "IMsgFabric.h"

namespace JsonParser
{
	class AcceptMsgFabric : public IMsgFabric
	{
	public:
		AcceptMsgFabric(const std::string &_version) :
			serverVersion(_version)
		{}

		// Унаследовано через IMsgFabric
		virtual Json::Value CreateJsValue() override;


	private:
		const std::string serverVersion;
	};
}