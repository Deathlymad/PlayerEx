#include "ExtensionLinker.h"

#include <iostream>

boost::asio::io_service ExtensionLinker::service_handler{};

ExtensionLinker::ExtensionLinker() : sock(service_handler), r(service_handler)
{
}

void ExtensionLinker::connect()
{
	auto t = r.resolve(boost::asio::ip::tcp::resolver::query{ "echo.websocket.org", "80" });
	boost::asio::connect(sock, t);
}

void ExtensionLinker::sendCSS(std::string css)
{
	beast::websocket::stream<boost::asio::ip::tcp::socket& >ws{ sock };
	ws.handshake("echo.websocket.org", "/");
	ws.write(boost::asio::buffer("c" + css));
}
void ExtensionLinker::sendFile(std::string path)
{

}

ExtensionLinker::~ExtensionLinker()
{
}
