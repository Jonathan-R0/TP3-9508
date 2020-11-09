#include "response.h"

#include <iostream>

#include "../common_src/parser.h"
#include "aceptador.h"
#include "getanswer.h"
#include "invalidanswer.h"
#include "postanswer.h"

#define GET_METHOD "GET"
#define POST_METHOD "PÓST"

Response::~Response() {}

Response* Response::create(Parser& parser) {
  if (parser.isMethod(GET_METHOD)) {
    return new GetAnswer();
  } else if (parser.isMethod(GET_METHOD)) {
    return new PostAnswer();
  }
  return new InvalidAnswer();
}
