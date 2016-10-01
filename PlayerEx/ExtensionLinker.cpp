#include "ExtensionLinker.h"
#include "Session.h"

#include <iostream>

ExtensionLinker::ExtensionLinker(Session* owner) : _owner(owner)
{
	// Set logging settings
	endpoint.set_error_channels(websocketpp::log::elevel::all);
	endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

	// Set the default message handler to the echo handler
	endpoint.set_message_handler(std::bind(
		&ExtensionLinker::echo_handler, this,
		std::placeholders::_1, std::placeholders::_2
	));
	websocketpp::open_handler;
	endpoint.set_open_handler([this](websocketpp::connection_hdl hdl) {
		connection = hdl;
	});
}

void ExtensionLinker::echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
	// write a new message
	if (msg->get_payload() == "reload")
		_owner->generateCSS();

	endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
}

void ExtensionLinker::run() {
	// Initialize Asio
	endpoint.init_asio();

	// Listen on port 9002
	endpoint.listen(9999);

	// Queues a connection accept operation
	endpoint.start_accept();

	// Start the Asio io_service run loop
	endpoint.run();
}

void ExtensionLinker::sendCSS(std::string& css)
{
	endpoint.send( connection, css, websocketpp::frame::opcode::TEXT);
}
void ExtensionLinker::sendFile(std::string& path)
{
}

ExtensionLinker::~ExtensionLinker()
{
	endpoint.stop();
}
