#pragma once

#include <set>
#include <string>

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::tcp;

namespace GEngine
{

namespace mnet
{

extern std::string IDENTIFICATION_MESSAGE;

class Server;

class TCPConnection : public boost::enable_shared_from_this<TCPConnection>
{
public:
	typedef boost::shared_ptr<TCPConnection> Pointer_t;

	//The data the client has received.
	std::vector<std::string> data_received;

	/**
	* Creates an instance of this class.
	*
	* Ensures that all instances are shared pointers.
	*
	* @param ioService The IO Service to use
	*/
	static Pointer_t create(boost::asio::io_service &ioService);

	/**
	* @return A reference to this connection's socket object.
	*/
	tcp::socket &socket();

	/**
	* Starts the TCP connection.
	*/
	void start(); //TODO: I think this function is the reason why every time a client sends a message to the server, the server sends its greeting back.

	void update();

	void close();

	void setParent(Server *the_parent);

	void write(std::string message);

	std::string getData();

private:
	TCPConnection(boost::asio::io_service &ioService);

	/**
	* Handles writing operations. Is not to be called directly.
	*
	* @param error Any error which may have been raised
	* @param bytesTransferred The number of bytes that were written
	*/
	void handleWrite(const boost::system::error_code &error, size_t bytesTransferred);

	void handleReceive(const boost::system::error_code &error, size_t bytesTransferred);

	//This connection's socket object
	tcp::socket connection_socket;
	//Contains any messages that are sent. Must be a member since the writes are asynchronous
	//std::string message_;
	std::string message_to_send;
	//A buffer to store received messages in. I wish this could use plain old std::strings.
	boost::array<char, 128> buffer;
	//The parent server object
	Server *parent;
};

typedef std::set<TCPConnection::Pointer_t> ClientSet_t;

class Server
{
public:
	Server();

	~Server();

	bool start(int port);

	//Updates the server. Run this in its own thread.
	void update();

	//Apparently this does nothing.
	void updateClients();

	void stop();

	void sendMessageToAll(std::string message);

	void setVerbose(bool value);

	//Set to false if you don't want it to output anything to the console.
	bool verbose = true;
private:
	void startAccept();
	void handleAccept(TCPConnection::Pointer_t connection, const boost::system::error_code &error);
      
	boost::asio::io_service io_service;
	tcp::acceptor *acceptor;
	ClientSet_t clients;

	bool run; //True as long as the server is supposed to run.
};

} // mnet

} //namespace GEngine
