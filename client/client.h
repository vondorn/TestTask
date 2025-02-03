#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class Client {
 public:
  Client() {}

  void connect() {
    try {
      tcp::resolver resolver(io_context);
      tcp::resolver::results_type endpoints =
          resolver.resolve("127.0.0.1", "12345");

      socket = new tcp::socket(io_context);
      boost::asio::connect(*socket, endpoints);
      std::cout << "                       CONNECTED\n";
    } catch (const std::exception& e) {
      std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout << "                       TRY RECONNECT" << std::endl;
      connect();
    }
  }

  void sendMessage(const std::string& message) {
    boost::asio::write(*socket, boost::asio::buffer(message));

    std::cout << "SENDED: " << message << std::endl;
  }

 private:
  boost::asio::io_context io_context;
  tcp::socket* socket;
  // tcp::resolver resolver;
};
