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
    return references[key];
  }
  void setReferenceTo(const std::string& key, const std::string& value) {
    std::unique_lock<std::mutex> lock(m);
    references[key] = value;
  }
};

#endif  // REFERENCEFOUNTAIN_H_
