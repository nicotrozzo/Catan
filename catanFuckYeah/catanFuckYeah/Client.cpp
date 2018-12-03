#include "Client.h"
#include <boost/lambda/lambda.hpp>

client::client() : deadline(*IO_handler)
{
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

/*PREGUNTAR QUE PASA, SI ES BLOQUEANTE O QUE CARAJO*/
/*PREGUNTAR POR EL PARAMETRO HOST QUE HACER*/
void client::startConnection(const char* host)
{
	if (!connected)
	{
		endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(host, PORT_STR));
		//boost::asio::connect(*socket, endpoint, error);	//BLOQUEANTE

		deadline.expires_from_now(boost::posix_time::milliseconds(750));
		error = boost::asio::error::would_block;		
		boost::asio::async_connect(*socket,endpoint,boost::lambda::var(error) = boost::lambda::_1 );
		deadline.async_wait(boost::lambda::var(error) = boost::asio::error::timed_out);
		IO_handler->run_one();
		
		if (!error)
		{
			connected = true;
			socket->non_blocking(true);
		}
	}
}

client::~client()
{
	delete client_resolver;
}
