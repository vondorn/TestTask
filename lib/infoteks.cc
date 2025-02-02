#include "infoteks.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

void sortAndReplace(std::string& str) {
  std::istringstream iss(str);
  std::vector<int> numbers;
  int num;
  while (iss >> num) {
    numbers.push_back(num);
  }

  std::sort(numbers.rbegin(), numbers.rend());

  std::ostringstream oss;
  for (int n : numbers) {
    if (!(n % 2)) {
      oss << "KB ";
    } else {
      oss << n << " ";
    }
  }

  str = oss.str();
  if (!str.empty()) {
    str.pop_back();
  }
}
  
int calculateSum(const std::string& str) {
  std::istringstream iss(str);
  std::string token;
  int sum = 0;
  while (iss >> token) {
    if (token != "KB") {
      sum += stoi(token);
    }
  }
  return sum;
}

bool checkLength(const std::string& str) {
  size_t length = str.size();
  return length > 2 && !(length % 32);
}
