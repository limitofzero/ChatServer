#include "GuidMsgFabric.h"

Json::Value JsonParser::GuidMsgFabric::CreateJsValue()
{
	Json::Value jsValue;
	jsValue["Message"]["GUID"] = guidClient;
	jsValue["Message"]["Content"] = msgClient;
	//�������� ��� ��� �������

	return Json::Value();
}
