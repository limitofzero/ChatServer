#pragma once

#include "IMsgFabric.h"

namespace JsonParser
{
	class GuidMsgFabric : public IMsgFabric
	{
	public:
		GuidMsgFabric(const std::string &_guid, const std::string &_message) :
			guidClient(_guid),
			msgClient(_message)
		{}

		// ”наследовано через IMsgFabric
		virtual Json::Value CreateJsValue() override;


	private:
		const std::string guidClient;
		const std::string msgClient;
		//добавить переменную времени
	};
}