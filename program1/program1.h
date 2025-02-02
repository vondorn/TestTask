#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "../lib/infoteks.h"
#include "../client/client.h"

class Program1 {
 public:
  Program1();
  void producerThread();
  void consumerThread();
  bool digitSpaceStroke(std::string& str);

 private:
  std::queue<std::string> buffer;
  std::mutex mtx;
  std::condition_variable cv;
  Client client;
};
