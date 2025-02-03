#include "program2.h"

void Program2::work() {
  while (1) {
    try {
      std::string str;
      server.readMessage(str);
      std::cout << "CHECKING... ";
      std::cout << (checkLength(str) ? "true" : "false") << std::endl;
    } catch (const std::exception& e) {
      std::cout << "TRY RECONNECT" << std::endl;
      server.connect();
    }
  }
}

int main() {
  Program2 p;
  try {
    p.work();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}