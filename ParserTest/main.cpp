#include "../TCPChatServer/Parser.h"
#include <assert.h>

int main()
{
	const std::string firstMessage = R"({
	"Authorizing":
	{
		"guid" : "Guid13",
		"password" : "password"
	}
})";

	const std::string secondMessage = R"({
	"Message":
	{
		"guid" : "Guid13",
		"content" : "content"
	}
})";

	const std::string thirstMessage = R"(	"Message":
	{
		"guid" : "Guid13",
		"content" : "content"
	})";

	JsonParser::Parser parser;
	auto obj = parser.ParseMessage("temp", firstMessage);
	assert(obj);

	auto obj2 = parser.ParseMessage("temp", secondMessage);
	assert(obj2);


	system("pause");
	return 0;
}