#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class Server {
 public:
  Server() { connect(); }

  void connect() {
    try {
      tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
      socket = new tcp::socket(io_context);
      acceptor.accept(*socket);
      std::cout << "SEVER ON\n";
    } catch (const std::exception& e) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      connect();
    }
  }

  void readMessage(std::string& message) {
    char data[256] = "";
    socket->read_some(boost::asio::buffer(data));
    std::cout << "READING..." << data << std::endl;
    message = data;
  }

 private:
  boost::asio::io_context io_context;
  tcp::socket* socket;
};