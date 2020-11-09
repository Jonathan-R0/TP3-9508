#include "invalidanswer.h"

#include "../common_src/parser.h"
#include "referencefountain.h"

std::string InvalidAnswer::generate(Parser& parser, Referencefountain& msg) {
  return "HTTP/1.1 405 METHOD NOT ALLOWED\n\n";
}
