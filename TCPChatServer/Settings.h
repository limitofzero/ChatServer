#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace ChatServer
{
	//класс для хранения настроек(паттерн singleton)
	struct Settings
	{
	public:
		Settings(const Settings &refSettings) = delete;
		Settings(Settings &&rrSettigs) = delete;
		Settings &operator=(const Settings &refSettings) = delete;

		//инстанцирует класс и возвращает ссылку на него(аргумент - путь к файлу конфига)
		static Settings &Instance();

		std::unordered_map<std::string, Json::Value> shemes;//схемы для валидации(ключ - наименование схемы)
		uint16_t secondsToDisconnect;//время до отключения клиента от сервера

	protected:
		Settings();

	private:
		//читает схему из файла и добавляет ее в shemes
		void ReadScheme(const std::string &nameOfSheme, const std::string &path);

		//читает ini файл настроек
		void ReadIniConfig(const std::string &path);
	};
}
