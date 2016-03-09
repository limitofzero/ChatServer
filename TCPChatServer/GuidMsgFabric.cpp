#include "GuidMsgFabric.h"

Json::Value JsonParser::GuidMsgFabric::CreateJsValue()
{
	Json::Value jsValue;
	jsValue["Message"]["GUID"] = guidClient;
	jsValue["Message"]["Content"] = msgClient;
	jsValue["Message"]["Time"] = timeReceive;

	return Json::Value();
}
