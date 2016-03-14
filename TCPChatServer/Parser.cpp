#include "Parser.h"

std::string JsonParser::Parser::CreateMessage(const IMsgFabric &fabricObjec)
{
	auto jsValue = fabricObjec.CreateJsValue();
	return jsWriter.write(jsValue);//���������� json ��������� � ������
}

bool JsonParser::Parser::IsLoad(const std::string &string)
{
	//������� ���� ����� ���������
	jsValue.clear();
	//���������� true ��� ������� �������� ������
	return jsReader.parse(string, jsValue);
}


