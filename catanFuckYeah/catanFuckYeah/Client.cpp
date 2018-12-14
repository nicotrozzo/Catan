#include "Client.h"
#include <boost/lambda/lambda.hpp>

client::client() : deadline(*IO_handler)
{
	error = boost::asio::error::would_block;
	hasToAsyncConnect = true;
}

void client::startConnection(const char* host)
{
	if (!connected)
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), PORT);
		deadline.expires_from_now(boost::posix_time::milliseconds(750));
		error = boost::asio::error::would_block;		
		if (hasToAsyncConnect)
		{
			socket->async_connect(endpoint,
				[this](boost::system::error_code error)
				{
					if (!error)
					{
						connected = true;
						hasToAsyncConnect = false;
						socket->non_blocking(true);
					}
				}
			);
			deadline.async_wait(
				[this](boost::system::error_code error)
				{
						hasToAsyncConnect = true;
				}
			);
			hasToAsyncConnect = false;
		}
		IO_handler->run_one();
		
	}
}

