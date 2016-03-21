#pragma once

#include <string>
#include <memory>

namespace ChatServer
{
	//структура для загрузги и хранения настроек
	struct Settings
	{
		//считывает настройки из ini-файла
		void Initialize(const std::string &path);

		//схемы для валидации
		std::string authotiringScheme;
		std::string messageScheme;

		uint16_t secondsToDisconnect;//время до отключения клиента от сервера
	};
}
