#pragma once

#include "connector.h"

#define SERVER_IP "localhost"

using namespace std;

class client : public connector
{
public:
	client();
	void startConnection(const char* host);
	virtual connectorType getType() { return CLIENT; };
	~client();

private:
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::deadline_timer deadline;
	boost::system::error_code error;
	string host;
	string path;
	string serverMessage;
	clientError err;
};

