#include "../TCPChatServer/Parser.h"
#include "../TCPChatServer/IMsgFabric.h"
#include "../TCPChatServer/AuthorizeMsgFabric.h"
#include "../TCPChatServer/AcceptMsgFabric.h"
#include "../TCPChatServer/GuidMsgFabric.h"
#include "../TCPChatServer/ErrorMsgFabric.h"
#include <assert.h>
#include <fstream>

std::string ReadMessageFromFile(const std::string &path);
void TestFabric(JsonParser::Parser &parser);

int main()
{

	JsonParser::Parser parser;

	auto firstMessage = ReadMessageFromFile("../test/message.json");
	auto obj = parser.ParseMessage("Guid13", firstMessage);
	assert(obj);

	auto secondMessage = ReadMessageFromFile("../test/authorizing.json");
	auto obj2 = parser.ParseMessage("Guid13", secondMessage);
	assert(obj2);

	//тест фабрики
	TestFabric(parser);

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

void TestFabric(JsonParser::Parser &parser)
{
	using namespace JsonParser;
	using msgFabricPtr = std::unique_ptr<JsonParser::IMsgFabric>;
	std::list<msgFabricPtr> listOfFabrics;

	listOfFabrics.emplace(listOfFabrics.end(), 
		std::make_unique<GuidMsgFabric>("guid", "Content of message", "16.23.1994"));
	listOfFabrics.emplace(listOfFabrics.end(), 
		std::make_unique<ErrorMsgFabric>(static_cast<ChatServer::SERVER_ERROR>(200)));
	listOfFabrics.emplace(listOfFabrics.end(), 
		std::make_unique<AuthorizeMsgFabric>(true));
	listOfFabrics.emplace(listOfFabrics.end(), 
		std::make_unique<AcceptMsgFabric>("1.2.33"));

	for (auto &i : listOfFabrics)
	{
		BOOST_LOG_TRIVIAL(info) << parser.CreateMessage(*i);
	}
}