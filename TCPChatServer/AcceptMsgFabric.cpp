#include "AcceptMsgFabric.h"

Json::Value JsonParser::AcceptMsgFabric::CreateJsValue()
{
	Json::Value jsValue;

	jsValue["Accept"]["Version"] = serverVersion;

	return jsValue;
}
