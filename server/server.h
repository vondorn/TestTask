#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class Server {
 public:
  Server() {
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
    socket = new tcp::socket(io_context);
    acceptor.accept(*socket);
    std::cout << "SEVER ON\n";
  }

  void readMessage(std::string& message) {
    char data[1024] = "";
    socket->read_some(boost::asio::buffer(data));
    std::cout << "READING..." << data << std::endl;
    message = data;
  }

 private:
  boost::asio::io_context io_context;
  tcp::socket* socket;
};