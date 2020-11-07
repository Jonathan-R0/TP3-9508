#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>

class Parser {
 private:
  std::string method;
  std::string resource;
  std::string protocol;
  std::string body;
  std::string root;
  void fillroot(std::string& rootfile);
  std::string rootfile;

 public:
  Parser(std::string& file);
  void operator()(std::string& alllines);

  // TEST ONLY
  void seeStuff() {
    std::cout << "Method: " << method << std::endl << std::endl;
    std::cout << "Resource: " << resource << std::endl << std::endl;
    std::cout << "Protocol: " << protocol << std::endl << std::endl;
    std::cout << "Body: " << body << std::endl << std::endl;
    std::cout << "Root: " << root << std::endl << std::endl;
  }
};

#endif  // PARSER_H_
