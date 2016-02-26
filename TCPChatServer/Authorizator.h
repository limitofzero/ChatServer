#pragma once

#include "ServerInterface.h"
#include <unordered_map>
#include <chrono>
#include <boost/asio/basic_deadline_timer.hpp>

namespace ChatServer
{
	using namespace boost;
	class BaseParser;
	//�����, �������������� �����������
	class Authorizator
	{
	public:


	private:
		std::unique_ptr<BaseParser> pParser;
		std::unordered_map<uint16_t, SocketPtr> socketsList;//������ ������� ��������� �����������
		std::unordered_map<uint16_t, asio::deadline_timer> timersList;//������ �������� ����������

		const std::chrono::seconds disconnectSeconds;
		uint16_t socketCounter{ 0 };//������� �������, ���������������� ��� ���������� ������ ������ � ������
	};
}