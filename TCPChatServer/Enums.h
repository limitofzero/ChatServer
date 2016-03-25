#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace ChatServer
{
	//перечисления типов сообщений пользователям
	enum class MSG_TYPE : uint8_t
	{
		MESSAGE = 0,//отпавить сообщение от пользователя
		ACCEPT,//подключение к серверу и запрос на логина и пароля
		AUTHORIZE, //удачная авторизация
		DISC_GUID,//отключение пользователя
		CON_GUID,//подключение пользователя
		DISCONNECT//отключение данного пользователя по таймеру
	};

	//перечисления типов ошибок на сервере(список будет расширяться)
	enum class SERVER_ERROR : uint8_t
	{
		PARSING = 200, //ошибка парсинга
		AUTHORIZE //ошибка авторизации(неверный логин или пароль)
	};


	//ошибка и их описание
	const std::unordered_map<SERVER_ERROR, std::string> errorsDescription
	{
		std::pair<SERVER_ERROR, std::string>(SERVER_ERROR::PARSING, "Ошибка парсинга"),
		std::pair<SERVER_ERROR, std::string>(SERVER_ERROR::AUTHORIZE, "Ошибка авторизации")
	};
}