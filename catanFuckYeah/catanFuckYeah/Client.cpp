#include "Client.h"
#include <boost/lambda/lambda.hpp>

client::client() : deadline(*IO_handler)
{
	hasToAsyncConnect = true;
}

/*PREGUNTAR QUE PASA, SI ES BLOQUEANTE O QUE CARAJO*/
/*PREGUNTAR POR EL PARAMETRO HOST QUE HACER*/
void client::startConnection(const char* host)
{
	if (!connected)
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), PORT);
		//endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(host, PORT_STR));
		//boost::asio::connect(*socket, endpoint, error);	//BLOQUEANTE

		deadline.expires_from_now(boost::posix_time::milliseconds(750));
		error = boost::asio::error::would_block;
		if (hasToAsyncConnect)
		{
			socket->async_connect(endpoint,
				[this](boost::system::error_code error)
				{
					if (!error)
					{
						cout << "ENTRE!" << endl;
						connected = true;
						hasToAsyncConnect = false;
						socket->non_blocking(true);
					}
					else
					{
						cout << "Entre con error" << endl;
					}
				}
			);
			deadline.async_wait(
				[this](boost::system::error_code error)
				{
					hasToAsyncConnect = true;
					cout << "Not timeout?" << endl;
					cout << error << " : " << error.message() << endl;
				}
			);
			hasToAsyncConnect = false;
		}
		IO_handler->run_one();
	}
}
