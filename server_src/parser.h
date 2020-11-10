#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>

class Parser {
 private:
  void fillroot(const std::string& rootfile);

 public:
  std::string method;
  std::string resource;
  std::string protocol;
  std::string body;
  std::string root;
  explicit Parser(const std::string& file);
  void operator()(std::string& alllines);
};

#endif  // PARSER_H_
