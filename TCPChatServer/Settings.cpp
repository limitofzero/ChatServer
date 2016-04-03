#include "Settings.h"
#include <json\json.h>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\ini_parser.hpp>
#include <boost\log\trivial.hpp>

namespace ChatServer
{
	Settings::Settings()
	{
		//������ ����� �� ������
		ReadScheme("authorizing", "../configs/schemes/authorizing.json");
		ReadScheme("message", "../configs/schemes/message.json");

		ReadIniConfig("../configs/config.ini");
	}

	Settings &Settings::Instance()
	{
		//�������������� ������ � ���������� ������ �� ����
		static Settings settings;
		return settings;
	}

	void Settings::ReadScheme(const std::string &nameOfSheme, const std::string &path)
	{
		std::ifstream in(path);
		if (!in.is_open())//���� �� ������� ������� ����
		{
			BOOST_LOG_TRIVIAL(fatal) << "File isn't closed(" << path << ")";
		}

		Json::Reader jsReader;
		Json::Value sheme;

		if (!jsReader.parse(in, sheme))//���� �� ������� ����������
		{
			in.close();
			BOOST_LOG_TRIVIAL(fatal) << "Uncorrect js value(" << nameOfSheme << ")";
		}
		
		//��������� ����� � ������
		shemes.emplace(nameOfSheme, sheme);
		in.close();
	}

	void Settings::ReadIniConfig(const std::string &path)
	{
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini(path, pt);

		secondsToDisconnect = pt.get<uint16_t>("Timer.seconds", 20);
	}
}
