#include "parser.h"

#include <fstream>
#include <sstream>
#include <vector>

void Parser::operator()(std::string& alllines) {
  std::string line;
  std::stringstream lines(alllines);

  lines >> method;
  lines >> resource;
  lines >> protocol;
  resource.erase(0, 1);
  std::cout << method << " /" << resource << " " << protocol << std::endl;
  bool isBody = false;
  getline(lines, line);  // La primera siempre me queda vacía.
  while (getline(lines, line)) {
    if (line.empty()) isBody = true;
    if (isBody) body += line + "\n";
    // std::cout << "En root appendeo: |" << line << "|\n";
  }
}

Parser::Parser(std::string& filename) { fillroot(filename); }

void Parser::fillroot(std::string& filename) {
  std::ifstream file;
  std::string line;
  file.open(filename);
  while (getline(file, line)) {
    root += line + "\n";
    //  std::cout << "En root appendeo: |" << line << "|\n";
  }
}
