#pragma once

#include <string>
#include <memory>

namespace ChatServer
{
	//��������� ��� �������� � �������� ��������
	struct Settings
	{
		//��������� ��������� �� ini-�����
		void Initialize(const std::string &path);

		//����� ��� ���������
		std::string authotiringScheme;
		std::string messageScheme;

		uint16_t secondsToDisconnect;//����� �� ���������� ������� �� �������
	};
}
