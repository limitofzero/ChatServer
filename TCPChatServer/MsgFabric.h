#pragma once

#include <string>
#include <json\json.h>

namespace JsonParser
{
	class JValueFabric
	{
	public:
		//������� Json::Value ������
		virtual Json::Value CreateJsValue() = 0;
	};
}