#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace ChatServer
{
	//����� �� �������(���� �� �������)
	//����� ��� �������� ��������(������� singleton)
	class Settings
	{
	public:
		static Settings &Instance(const std::string &pathToConfig);

	protected:


	private:
		//����� ��� ���������(���� - ������������ �����)
		std::unordered_map<std::string, std::string> shemes;

		uint16_t secondsToDisconnect;//����� �� ���������� ������� �� �������
	};
}
