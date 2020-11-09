#ifndef REFERENCEFOUNTAIN_H_
#define REFERENCEFOUNTAIN_H_

#include <iostream>
#include <map>
#include <mutex>
#include <string>

class Referencefountain {
 private:
  std::map<std::string, std::string> references;
  std::mutex m;

 public:
  std::string getReferenceFrom(const std::string& key) {
    std::unique_lock<std::mutex> lock(m);
    // std::cout << "Looking up: " << key << std::endl;
    return references[key];
  }
  void setReferenceTo(std::string key, const std::string value) {
    std::unique_lock<std::mutex> lock(m);
    // std::cout << "Saving key: " << key << " and value: " << value <<
    // std::endl;
    references[key] = value;
  }
};

#endif  // REFERENCEFOUNTAIN_H_
