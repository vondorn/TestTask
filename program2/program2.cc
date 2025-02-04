#include "program2.h"

void Program2::work() {
  while (1) {
    std::string str;
    try {
      std::cout << "CHECKING... ";
      server.readMessage(str);
    } catch (const std::exception& e) {
      server.connect();
      server.readMessage(str);
    }
    std::cout << (checkLength(str) ? "true" : "false") << std::endl;
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