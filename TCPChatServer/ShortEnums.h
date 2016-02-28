#pragma once

#include <boost/asio.hpp>
#include <memory>

namespace ChatServer
{

	using Socket = boost::asio::ip::tcp::socket;
	using SocketPtr = std::shared_ptr<Socket>;
}