#pragma once

#include "IMsgFabric.h"
#include "Enums.h"

namespace JsonParser
{
	class ErrorMsgFabric : public IMsgFabric
	{
	public:
		ErrorMsgFabric(const ChatServer::SERVER_ERROR code) :
			errorCode(code)
		{}

		// Унаследовано через IMsgFabric
		virtual Json::Value CreateJsValue() override;


	private:
		const ChatServer::SERVER_ERROR errorCode;
	};
}
