#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace ChatServer
{
	//������������ ����� ��������� �������������
	enum class MSG_TYPE : uint8_t
	{
		MESSAGE = 0,//�������� ��������� �� ������������
		ACCEPT,//����������� � ������� � ������ �� ������ � ������
		AUTHORIZE, //������� �����������
		DISC_GUID,//���������� ������������
		CON_GUID,//����������� ������������
		DISCONNECT//���������� ������� ������������ �� �������
	};

	//������������ ����� ������ �� �������(������ ����� �����������)
	enum class SERVER_ERROR : uint8_t
	{
		PARSING = 200, //������ ��������
		AUTHORIZE //������ �����������(�������� ����� ��� ������)
	};


	//������ � �� ��������
	const std::unordered_map<SERVER_ERROR, std::string> errorsDescription
	{
		emplace(SERVER_ERROR::PARSING, "������ ��������"),
		emplace(SERVER_ERROR::AUTHORIZE, "������ �����������")
	};
}