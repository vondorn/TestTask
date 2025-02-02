#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;         

    // Указываем адрес и порт сервера
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
        resolver.resolve("127.0.0.1", "12345");

    // Создаём сокет и подключаемся к серверу
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    std::cout << "Подключение к серверу установлено!" << std::endl;
    while (1) {
      // Отправляем строку серверу
      std::string message = "Привет, сервер!";
      boost::asio::write(socket, boost::asio::buffer(message));

      std::cout << "Сообщение отправлено: " << message << std::endl;
    }
  } catch (std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }

  return 0;
}