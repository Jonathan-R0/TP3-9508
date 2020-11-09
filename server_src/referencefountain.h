#ifndef REFERENCEFOUNTAIN_H_
#define REFERENCEFOUNTAIN_H_

#include <map>
#include <mutex>

class Referencefountain {
 private:
  std::map<std::string, std::string> references;
  std::mutex m;

 public:
  std::string getReferenceFrom(std::string& key) {
    std::unique_lock<std::mutex> lock(m);
    return references[key];
  }
  void setReferenceTo(std::string key, std::string value) {
    std::unique_lock<std::mutex> lock(m);
    references[key] = value;
  }
};

#endif  // REFERENCEFOUNTAIN_H_
