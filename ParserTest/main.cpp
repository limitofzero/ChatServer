#include "../TCPChatServer/Parser.h"
#include <assert.h>
#include <fstream>

std::string ReadMessageFromFile(const std::string &path);

int main()
{

	JsonParser::Parser parser;

	auto firstMessage = ReadMessageFromFile("../test/message.json");
	auto obj = parser.ParseMessage("temp", firstMessage);
	assert(obj);

	auto secondMessage = ReadMessageFromFile("../test/authorizing.json");
	auto obj2 = parser.ParseMessage("temp", secondMessage);
	assert(obj2);


	system("pause");
	return 0;
}

std::string ReadMessageFromFile(const std::string &path)
{
	std::string message = "";
	std::ifstream in(path);
	if (in.is_open())
	{
		std::getline(in, message, '\0');
		BOOST_LOG_TRIVIAL(info) << message;
	}
	else
	{
		BOOST_LOG_TRIVIAL(fatal) << "File didn't open";
	}

	in.close();
	return message;
}