#include "Acceptor.h"
#include <boost/log/trivial.hpp>

namespace ChatServer
{

	void Acceptor::Start()
	{
		//�������� ������� �����
		asioAcceptor.async_accept(socket,
			[this](const system::error_code &_errorCode)
		{
			OnAccept(_errorCode);
		});
	}

	void Acceptor::OnAccept(const system::error_code & _errorCode)
	{
		if (_errorCode)
		{
			if (_errorCode != asio::error::operation_aborted)
			{
				BOOST_LOG_TRIVIAL(error) << _errorCode.message();
			}
			return;
		}
		else
		{
			//���� ������������ ��� ������
			rServer.CreateConnection(std::move(socket));
		}

		socket = asio::ip::tcp::socket(rService);
		Start();//����� �������� ���������
	}
}