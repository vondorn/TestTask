#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "../client/client.h"
#include "../lib/infoteks.h"

class Program1 {
 public:
  Program1() {}
  void work();
  void trySend(const std::string& str);

 private:
  void producerThread();
  void consumerThread();
  bool digitSpaceStroke(std::string& str);
  std::queue<std::string> buffer;
  std::mutex mtx;
  std::condition_variable cv;
  Client client;
  std::string lastMessage;
};
