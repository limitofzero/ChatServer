#pragma once

#include "ServerInterface.h"
#include <unordered_map>
#include <chrono>
#include <boost/asio/basic_deadline_timer.hpp>

namespace ChatServer
{
	using namespace boost;
	class BaseParser;
	//класс, авторизирующий подключения
	class Authorizator
	{
	public:


	private:
		std::unique_ptr<BaseParser> pParser;
		std::unordered_map<uint16_t, SocketPtr> socketsList;//список сокетов ожидающих подключение
		std::unordered_map<uint16_t, asio::deadline_timer> timersList;//список таймеров отключения

		const std::chrono::seconds disconnectSeconds;
		uint16_t socketCounter{ 0 };//счетчик сокетов, инкрементируется при добавлении нового сокета в список
	};
}