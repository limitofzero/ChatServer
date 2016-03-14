#pragma once

#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <memory>
#include "ICommand.h"

namespace ChatServer
{

	using Socket = boost::asio::ip::tcp::socket;
	using SocketPtr = std::shared_ptr<Socket>;
	using OptionCommand = boost::optional<Command::ICommand>;
}