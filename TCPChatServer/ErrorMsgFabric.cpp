#include "ErrorMsgFabric.h"

Json::Value JsonParser::ErrorMsgFabric::CreateJsValue() const
{
	Json::Value jsValue;
	jsValue["Error"]["Code"] = static_cast<uint8_t>(errorCode);

	//���� ������ �� ����
	if (ChatServer::errorsDescription.find(errorCode) != ChatServer::errorsDescription.end())
	{
		//���� �������, �� ���������� � ���������
		jsValue["Error"]["Descripriprion"] = ChatServer::errorsDescription.at(errorCode);
	}
	else
	{
		//���� � ������ ��� �������� - ��������� ��������� � ����������� ������
		jsValue["Error"]["Descripriprion"] = "Unknown error!";
	}

	return jsValue;
}
