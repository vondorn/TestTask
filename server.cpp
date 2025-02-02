#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;

    // Создаём акцептор, который слушает порт 12345
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

    std::cout << "Сервер запущен. Ожидание подключения клиента..." << std::endl;

    // Ожидаем подключения клиента
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    std::cout << "Клиент подключен!" << std::endl;
    while (1) {
      // Читаем данные от клиента
      char data[1024];
      size_t length = socket.read_some(boost::asio::buffer(data));

      // Выводим полученную строку
      std::cout << "Получено сообщение: " << std::string(data, length)
                << std::endl;
    }
  } catch (std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }

  return 0;
}