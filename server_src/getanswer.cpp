#include "getanswer.h"

#include "../common_src/parser.h"
#include "referencefountain.h"

std::string GetAnswer::generate(Parser& parser, Referencefountain& msg) {
  if (!parser.resource.empty()) {
    std::string htmlcode = msg.getReferenceFrom(parser.resource);
    if (htmlcode != "") {
      return "HTTP 200 OK\n\n" + htmlcode;
    } else {
      return "HTTP 404 NOT FOUND\n\n";
    }
  }
  return "HTTP 200 OK\nContent-Type: text/html\n\n" + parser.root;
}
