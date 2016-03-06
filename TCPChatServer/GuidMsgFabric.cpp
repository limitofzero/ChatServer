#include "GuidMsgFabric.h"

Json::Value JsonParser::GuidMsgFabric::CreateJsValue()
{
	Json::Value jsValue;
	jsValue["Message"]["GUID"] = guidClient;
	jsValue["Message"]["Content"] = msgClient;
	//добавить код для времени

	return Json::Value();
}
