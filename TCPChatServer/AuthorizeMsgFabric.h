#pragma once

#include "IMsgFabric.h"

namespace JsonParser
{
	class AuthorizeMsgFabric : public IMsgFabric
	{
	public:
		AuthorizeMsgFabric(const bool _authorize) :
			isAuthorized(_authorize)
		{}

		// Унаследовано через IMsgFabric
		virtual Json::Value CreateJsValue() override;


	private:
		const bool isAuthorized;
	};
}