#include <string>

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <websocketpp/config/boost_config.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <boost\asio.hpp>
#include <websocketpp\server.hpp>


typedef websocketpp::server<websocketpp::config::asio> server;

class Session;

#pragma once
class ExtensionLinker
{
public:
	ExtensionLinker(Session*);

	void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg);

	void run();

	void sendCSS(std::string&);
	void sendFile(std::string&);
	
	~ExtensionLinker();
private:
	Session* _owner;
	server endpoint;
	websocketpp::connection_hdl connection;
};