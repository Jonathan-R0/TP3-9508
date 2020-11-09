#include "postanswer.h"

#include "../common_src/parser.h"
#include "referencefountain.h"

std::string PostAnswer::generate(Parser& parser, Referencefountain& msg) {
  if (!parser.resource.empty()) {
    msg.setReferenceTo(parser.resource, parser.body);
    return "HTTP/1.1 200 OK\n\n" + parser.body;
  }
  return "HTTP 403 FORBIDDEN\n\n";
}
