#pragma once

#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <memory>

namespace ChatServer
{
	using Socket = boost::asio::ip::tcp::socket;
	using SocketPtr = std::shared_ptr<Socket>;
}