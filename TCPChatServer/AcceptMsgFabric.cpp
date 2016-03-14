#include "AcceptMsgFabric.h"

Json::Value JsonParser::AcceptMsgFabric::CreateJsValue() const
{
	Json::Value jsValue;

	jsValue["Accept"]["Version"] = serverVersion;

	return jsValue;
}
