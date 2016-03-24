#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace ChatServer
{
	//задел на будущее(пока не трогать)
	//класс для хранения настроек(паттерн singleton)
	class Settings
	{
	public:
		static Settings &Instance(const std::string &pathToConfig);

	protected:


	private:
		//схемы для валидации(ключ - наименование схемы)
		std::unordered_map<std::string, std::string> shemes;

		uint16_t secondsToDisconnect;//время до отключения клиента от сервера
	};
}
