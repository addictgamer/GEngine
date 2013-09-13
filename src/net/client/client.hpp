/* Please refer to license.txt */

#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>

namespace GEngine
{

namespace mnet
{

class Client : public boost::enable_shared_from_this<Client>
{
private:
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::resolver *resolver;
	boost::asio::ip::tcp::resolver::query *query;
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator;
	boost::asio::ip::tcp::socket *socket;

	boost::array<char, 128> buffer;

	bool run = true;
public:
	typedef boost::shared_ptr<Client> Pointer_t;

	//static Pointer_t create(boost::asio::io_service &ioService);

	void handleWrite(const boost::system::error_code &error, size_t bytes_transferred_);

	void handleRead(const boost::system::error_code &error, size_t bytes_transferred_);

	std::vector<std::string> data_received; //Stores the data received so far.

	Client();
	~Client();

	/*
	Initializes a brand new client and attempts to connect to the specified host.
	Returns false on failure.
	TODO: Update to use the error module.
	Parameters:
		std::string host : the host to connect to.
		std::string port : the port to connect to.
	*/
	bool newConnection(std::string host, int port);

	void update();

	void stop();

	/*
	Returns true if the client is running.
	Returns false if the client has stopped (such as when connection to the server is lost.)
	*/
	bool running();

	void sendMessage(std::string message);

	/*
	Returns the data.
	One problem I foresee with this is getting more data than is being deciphered.
	*/
	std::string getData();
};

} //namespace mnet

} //namespace GEngine
