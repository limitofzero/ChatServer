#pragma once

#include <string>
#include <json\json.h>

namespace JsonParser
{
	class JValueFabric
	{
	public:
		//создать Json::Value объект
		virtual Json::Value CreateJsValue() = 0;
	};
}