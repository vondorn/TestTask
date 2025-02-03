#include "program1.h"

#include <algorithm>
#include <cctype>

#include "../lib/infoteks.h"

void Program1::work() {
  std::thread producer([this]() { producerThread(); });
  std::thread consumer([this]() { consumerThread(); });

  producer.join();
  consumer.join();
}

void Program1::producerThread() {
  while (1) {
    std::cout << "ENTER A STRING: ";
    std::string str;
    getline(std::cin, str);

    if (str.size() > 64 || !digitSpaceStroke(str)) {
      std::cout << "INVALID INPUT\n";
      continue;
    }

    sortAndReplace(str);

    {
      std::unique_lock<std::mutex> lock(mtx);
      buffer.push(str);
    }

    cv.notify_one();
  }
}

void Program1::consumerThread() {
  while (true) {
    std::string str;

    {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [this] { return !buffer.empty(); });

      str = buffer.front();
      buffer.pop();
    }

    int sum = calculateSum(str);
    std::cout << str << "\t\t\t" << sum << std::endl;
    client.sendMessage(str);
  }
}

bool Program1::digitSpaceStroke(std::string& str) {
  bool res = 1;
  for (auto i : str) {
    if (!isdigit(i) && !isspace(i)) {
      res = 0;
    }
  }
  return res;
}

int main() {
  Program1 p;
  try {
    p.work();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}

