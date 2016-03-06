#pragma once

#include <string>
#include <json\json.h>

namespace JsonParser
{
	//������� ������������ ����� ��� �������� Json �������
	class IMsgFabric 
	{
	public:
		//������� Json::Value ������
		virtual Json::Value CreateJsValue() = 0;
	};
}