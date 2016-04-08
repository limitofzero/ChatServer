#pragma once
#include "ICommand.h"
#include <boost\optional\optional.hpp>
#include <memory>

namespace ChatServer
{
	using OptionCommand = boost::optional<std::unique_ptr<Command::ICommand>>;
}