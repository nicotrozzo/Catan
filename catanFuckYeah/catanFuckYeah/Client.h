#pragma once

#include "connector.h"

#define SERVER_IP "localhost"

using namespace std;

class client : public connector
{
public:
	client();
	bool startConnection(const char* host);
	virtual connectorType getType() { return CLIENT; };
	~client();

private:
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	string host;
	string path;
	string serverMessage;
	clientError err;
};

