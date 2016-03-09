#include "ErrorMsgFabric.h"

Json::Value JsonParser::ErrorMsgFabric::CreateJsValue()
{
	Json::Value jsValue;
	jsValue["Error"]["Code"] = static_cast<uint8_t>(errorCode);

	//ищем ошибку по коду
	if (ChatServer::errorsDescription.find(errorCode) != ChatServer::errorsDescription.end())
	{
		//если нашлась, то отправляем в сообщении
		jsValue["Error"]["Descripriprion"] = ChatServer::errorsDescription.at(errorCode);
	}
	else
	{
		//если у ошибки нет описания - отправить сообщение о неизвестной ошибке
		jsValue["Error"]["Descripriprion"] = "Unknown error!";
	}

	return jsValue;
}
