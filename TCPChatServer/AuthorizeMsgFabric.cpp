#include "AuthorizeMsgFabric.h"

Json::Value JsonParser::AuthorizeMsgFabric::CreateJsValue()
{
	Json::Value jsValue;
	jsValue["Authorized"]["Success"] = isAuthorized;

	return Json::Value();
}
