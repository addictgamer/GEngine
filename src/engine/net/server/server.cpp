#include "server.hpp"

#include <iostream>

namespace mnet {

std::string IDENTIFICATION_MESSAGE = "HALLO!\n";

TCPConnection::Pointer_t TCPConnection::create(boost::asio::io_service &ioService)
{
	return Pointer_t(new TCPConnection(ioService));
}

tcp::socket &TCPConnection::socket()
{
	return connection_socket;
}

void TCPConnection::start()
{
	message_to_send = IDENTIFICATION_MESSAGE;
  
	boost::asio::async_write(connection_socket, boost::asio::buffer(message_to_send), boost::bind(&TCPConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  
	connection_socket.async_receive(boost::asio::buffer(buffer.data(), buffer.size()), boost::bind(&TCPConnection::handleReceive, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::update()
{
}

void TCPConnection::close()
{
	connection_socket.close();
}

void TCPConnection::setParent(Server *the_parent)
{
	parent = the_parent;
}

void TCPConnection::write(std::string message)
{
	boost::asio::async_write(connection_socket, boost::asio::buffer(message), boost::bind(&TCPConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

std::string TCPConnection::getData()
{
	std::string the_data; //The data.

	if (data_received.size() != 0)
	{
		the_data = data_received[0];
		data_received.erase(data_received.begin()); //Remove the data from the vector -- it's not needed there anymore.
	}

	return the_data;
}

TCPConnection::TCPConnection(boost::asio::io_service &ioService) : connection_socket(ioService), parent(nullptr) {}

void TCPConnection::handleWrite(const boost::system::error_code &error, size_t bytesTransferred)
{
	// TODO
	//TODO what?
}

void TCPConnection::handleReceive(const boost::system::error_code &error, size_t bytesTransferred)
{
	if (error.value() == boost::asio::error::eof)
	{
		if (parent->verbose)
		{
			std::cout << "[Server] Client at " << connection_socket.remote_endpoint().address().to_string() << " closed the connection." << std::endl;
		}
		close();
		return;
	}
	char *message = new char[bytesTransferred + 1];
	strncpy(message, buffer.data(), bytesTransferred);
	message[bytesTransferred] = '\0';
	if (parent->verbose)
	{
		std::cout << "[Server] Client sent message \"" << message << "\"." << std::endl;
	}
	//data_received.push_back(message); //Save the message. //TODO: Uncomment this later. We need to access the data received in the program.
	delete message;
  
	connection_socket.async_receive(boost::asio::buffer(buffer.data(), buffer.size()), boost::bind(&TCPConnection::handleReceive, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

Server::Server()
{
	run = true;
}

Server::~Server()
{
	if (acceptor)
	{
		delete acceptor;
	}
}

bool Server::start(int port)
{
	acceptor = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port));
	startAccept();
	return true;
}

void Server::update()
{
	while (run) //Because whenever a client crashes boost will throw an exception and this loop will prevent the server from terminating early.
	{
		try
		{
			io_service.run();
		}
		catch(...)
		{
		}
	}
}

void Server::updateClients()
{
	ClientSet_t::iterator iter = clients.begin(); 
	while (iter != clients.end())
	{
		if (!(*iter)->socket().is_open())
		{
			clients.erase(iter++);
			continue;
		}
		(*iter)->update();
		++iter;
	}
}

void Server::stop()
{
	io_service.stop();
	run = false;
}

void Server::startAccept()
{
	TCPConnection::Pointer_t newConnection = TCPConnection::create(acceptor->get_io_service());
	acceptor->async_accept(newConnection->socket(), boost::bind(&Server::handleAccept, this, newConnection, boost::asio::placeholders::error));
	short port = acceptor->local_endpoint().port();
	if (verbose)
	{
		std::cout << "[Server] Server listening at " << acceptor->local_endpoint().address().to_string() << ":" << port << "." << std::endl;
	}
}

void Server::handleAccept(TCPConnection::Pointer_t newConnection, const boost::system::error_code &error)
{
	if (verbose)
	{
		std::cout << "[Server] Incoming connection from " << newConnection->socket().remote_endpoint().address().to_string() << "." << std::endl;
	}

	if (!error)
	{
		newConnection->setParent(this);
		newConnection->start();
		clients.insert(newConnection);
	}

	startAccept();
}

void Server::sendMessageToAll(std::string message)
{
	if (verbose)
	{
		std::cout << "[SERVER] Sending message: \"" << message << "\"\n";
	}
	ClientSet_t::iterator iter = clients.begin(); 
	while (iter != clients.end())
	{
		if (!(*iter)->socket().is_open())
		{
			clients.erase(iter++);
			continue;
		}
		(*iter)->write(message);
		++iter;
	}
}
void Server::setVerbose(bool value)
{
	verbose = value;
}

} // mnet
