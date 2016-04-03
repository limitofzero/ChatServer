#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace ChatServer
{
	//����� ��� �������� ��������(������� singleton)
	struct Settings
	{
	public:
		Settings(const Settings &refSettings) = delete;
		Settings(Settings &&rrSettigs) = delete;
		Settings &operator=(const Settings &refSettings) = delete;

		//������������ ����� � ���������� ������ �� ����(�������� - ���� � ����� �������)
		static Settings &Instance();

		std::unordered_map<std::string, Json::Value> shemes;//����� ��� ���������(���� - ������������ �����)
		uint16_t secondsToDisconnect;//����� �� ���������� ������� �� �������

	protected:
		Settings();

	private:
		//������ ����� �� ����� � ��������� �� � shemes
		void ReadScheme(const std::string &nameOfSheme, const std::string &path);

		//������ ini ���� ��������
		void ReadIniConfig(const std::string &path);
	};
}
