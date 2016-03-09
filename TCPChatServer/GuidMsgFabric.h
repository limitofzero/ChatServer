#pragma once

#include "IMsgFabric.h"

namespace JsonParser
{
	class GuidMsgFabric : public IMsgFabric
	{
	public:
		GuidMsgFabric(const std::string &_guid, const std::string &_message, const std::string &_time) :
			guidClient(_guid),
			msgClient(_message),
			timeReceive(_time)
		{}

		// ������������ ����� IMsgFabric
		virtual Json::Value CreateJsValue() override;


	private:
		const std::string guidClient;
		const std::string msgClient;
		const std::string timeReceive;
	};
}