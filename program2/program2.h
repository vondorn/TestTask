#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "../lib/infoteks.h"
#include "../server/server.h"

class Program2 {
 public:
  Program2() {}
	void work();

 private:
  Server server;
};