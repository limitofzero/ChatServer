#pragma once

#include <string>
#include <json\json.h>

namespace JsonParser
{
	//базовый Интерфейсный класс для создания Json объекта
	class IMsgFabric 
	{
	public:
		//создать Json::Value объект
		virtual Json::Value CreateJsValue() const = 0;
	};
}