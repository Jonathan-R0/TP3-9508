#include "postanswer.h"

#include "parser.h"
#include "referencefountain.h"

#define OK_POSTANSWER "HTTP/1.1 200 OK\n"
#define ERROR_POSTANSWER "HTTP/1.1 403 FORBIDDEN\n"

std::string PostAnswer::generate(Parser& parser, Referencefountain& msg) {
  if (!parser.resource.empty()) {
    msg.setReferenceTo(parser.resource, parser.body);
    return OK_POSTANSWER + parser.body;
  }
  return ERROR_POSTANSWER;
}
