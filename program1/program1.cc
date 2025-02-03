#include "program1.h"

#include <algorithm>
#include <cctype>

#include "../lib/infoteks.h"

void Program1::work() {
  std::thread connecter([this]() { client.connect(); });
  std::thread producer([this]() { producerThread(); });
  std::thread consumer([this]() { consumerThread(); });

  producer.join();
  consumer.join();
}

void Program1::producerThread() {
  while (1) {
    std::string str;
    getline(std::cin, str);
    std::cout << "ENTERED STRING: " << str << std::endl;

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
  // std::this_thread::sleep_for(std::chrono::seconds(2));

  while (true) {
    std::string str;
    // size_t previousSize = buffer.size();
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [this] { return !buffer.empty(); });

      str = buffer.front();
      buffer.pop();
      std::cout << "EDITED STRING: " << str << std::endl;
    }

    // int sum = calculateSum(str);
    trySend(str);
  }
}

void Program1::trySend(const std::string& str) {
  // if ()
  try {
    client.sendMessage(str);
  } catch (const std::exception& e) {
    std::cout << "                         RECONNECT... " << std::endl;
    client.connect();
    trySend(str);
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
