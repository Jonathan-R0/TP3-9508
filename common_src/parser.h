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

  // TEST ONLY
  /*void seeStuff() {
    std::cout << "Method: |" << method << "|\n" << std::endl;
    std::cout << "Resource: |" << resource << "|\n" << std::endl;
    std::cout << "Protocol: |" << protocol << "|\n" << std::endl;
    std::cout << "Body: |" << body << "|\n" << std::endl;
    std::cout << "Root: |" << root << "|\n" << std::endl;
  }*/
};

#endif  // PARSER_H_
