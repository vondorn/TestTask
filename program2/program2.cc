#include "program2.h"

void Program2::work() {
  while (1) {
    std::string str;
    server.readMessage(str);
    std::cout << "CHECKING: ";
    std::cout << (checkLength(str) ? "true" : "false") << std::endl;
  }
}

int main() {
  Program2 p;
  p.work();
  return 0;
}