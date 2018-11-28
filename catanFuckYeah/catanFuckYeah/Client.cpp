#include "Client.h"

client::client()
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
		boost::system::error_code error;
		boost::asio::connect(*socket, endpoint, error);
		if (!error)
		{
			connected = true;
		}
		socket->non_blocking(true);
	}
}

client::~client()
{
	delete client_resolver;
}
