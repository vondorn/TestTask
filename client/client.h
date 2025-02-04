#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class Client {
 public:
  Client() {}

  bool connect() {
    bool res = 0;
    try {
      tcp::resolver resolver(io_context);
      tcp::resolver::results_type endpoints =
          resolver.resolve("127.0.0.1", "12345");

      socket = new tcp::socket(io_context);
      boost::asio::connect(*socket, endpoints);
      std::cout << "                       CONNECTED\n";
      res = 1;
    } catch (const std::exception& e) {
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return res;
  }

  void sendMessage(const std::string& message) {
    boost::asio::write(*socket, boost::asio::buffer(message));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "SENDED: " << message << std::endl;
  }

 private:
  boost::asio::io_context io_context;
  tcp::socket* socket;
  // tcp::resolver resolver;
};
