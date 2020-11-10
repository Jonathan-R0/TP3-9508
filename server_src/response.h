#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <string>

#include "../common_src/parser.h"
#include "referencefountain.h"

class Response {
 public:
  static Response* create(const Parser& parser);
  virtual ~Response() = 0;
  virtual std::string generate(Parser& parser, Referencefountain& msg) = 0;
};

#endif  // RESPONSE_H_
