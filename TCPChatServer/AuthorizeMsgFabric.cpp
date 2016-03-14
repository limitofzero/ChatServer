#include "AuthorizeMsgFabric.h"

Json::Value JsonParser::AuthorizeMsgFabric::CreateJsValue() const
{
	Json::Value jsValue;
	jsValue["Authorized"]["Success"] = isAuthorized;

	return Json::Value();
}
