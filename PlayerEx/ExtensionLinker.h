#include <string>

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <boost\asio.hpp>
#include <beast\websocket.hpp>


#pragma once
class ExtensionLinker
{
public:
	ExtensionLinker();
	
	void connect();

	void sendCSS(std::string);
	void sendFile(std::string);
	
	~ExtensionLinker();
private:
	static boost::asio::io_service service_handler;
	boost::asio::ip::tcp::socket sock;
	boost::asio::ip::tcp::resolver r;
};