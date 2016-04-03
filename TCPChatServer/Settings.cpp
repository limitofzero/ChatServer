#include "Settings.h"
#include <json\json.h>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\ini_parser.hpp>
#include <boost\log\trivial.hpp>

namespace ChatServer
{
	Settings::Settings()
	{
		//читаем схемы из файлов
		ReadScheme("Authorizing", "/configs/shemes/Authorizing.json");
		ReadScheme("Message", "/configs/shemes/Message.json");

		ReadIniConfig("/configs/config.ini");
	}

	Settings &Settings::Instance()
	{
		//инициализируем объект и возвращаем ссылку на него
		static Settings settings;
		return settings;
	}

	void Settings::ReadScheme(const std::string &nameOfSheme, const std::string &path)
	{
		std::ifstream in(path);
		if (!in.is_open())//если не удалось открыть файл
		{
			BOOST_LOG_TRIVIAL(fatal) << "File isn't closed(" << path << ")";
		}

		Json::Reader jsReader;
		Json::Value sheme;

		if (!jsReader.parse(in, sheme))//если не удалось распарсить
		{
			in.close();
			BOOST_LOG_TRIVIAL(fatal) << "Uncorrect js value(" << nameOfSheme << ")";
		}
		
		//добавляем схему в список
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
