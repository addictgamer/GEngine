/* Please refer to license.txt */

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

#include "client.hpp"

#include "../../string/string.hpp"

#include <iostream>

using boost::asio::ip::tcp;

namespace GEngine
{

namespace mnet
{

Client::Client()
{
	resolver = new tcp::resolver(io_service);
	query = nullptr;
	socket = nullptr;
}

Client::~Client()
{
	if (resolver)
	{
		delete resolver;
	}
	if (query)
	{
		delete query;
	}
	if (socket)
	{
		delete socket;
	}
}

bool Client::newConnection(std::string host, int port)
{
	try
	{
		query = new tcp::resolver::query(host, mstring::toString(port));
		endpoint_iterator = resolver->resolve(*query);

		socket = new tcp::socket(io_service); //Create the socket.

		boost::asio::connect(*socket, endpoint_iterator); //Connect the socket.
	}
	catch (std::exception& e)
	{
		std::cerr << "[CLIENT] FATAL ERROR: " << e.what() << std::endl; //Report the error.
		return false; //Failure, aww.
	}

	return true; //Success by default.
}

void Client::update()
{
	socket->async_read_some(boost::asio::buffer(buffer), boost::bind(&Client::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	try
	{
		io_service.run();
	}
	catch (...)
	{
		std::cout << "[CLIENT] Exception caught for io_service.run in Client::update().\n";
		this->stop();
	}
}

void Client::stop()
{
	run = false; //Stop running.
	io_service.stop();
}

bool Client::running()
{
	return run;
}

void Client::sendMessage(std::string message)
{
	boost::asio::async_write(*socket, boost::asio::buffer(message), boost::bind(&Client::handleWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Client::handleWrite(const boost::system::error_code &error, size_t bytes_transferred_)
{
}

void Client::handleRead(const boost::system::error_code &error, size_t bytes_transferred_)
{
	if (error)
	{
		std::cout << "[CLIENT] Boost passed error to Client::handleRead(). Aborting.\n";
		//TODO: Properly handle error.
		this->stop();
		return;
	}
	else
	{
		if (bytes_transferred_ != 0)
		{
			std::string new_data(buffer.begin(), buffer.begin() + bytes_transferred_); //Convert the buffer.

			data_received.push_back(new_data); //Save the new data.
		}

		socket->async_read_some(boost::asio::buffer(buffer), boost::bind(&Client::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
}

std::string Client::getData()
{
	std::string the_data; //The data.

	if (data_received.size() != 0)
	{
		the_data = data_received[0];
		data_received.erase(data_received.begin()); //Remove the data from the vector -- it's not needed there anymore.
	}

	return the_data;
}

} //namespace mnet

} //namespace GEngine
