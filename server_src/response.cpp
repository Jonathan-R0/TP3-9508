#include "response.h"

#include <iostream>

#include "aceptador.h"
#include "getanswer.h"
#include "invalidanswer.h"
#include "parser.h"
#include "postanswer.h"

#define GET_METHOD "GET"
#define POST_METHOD "POST"

Response::~Response() {}

Response* Response::create(const Parser& parser) {
  if (parser.method == GET_METHOD) {
    return new GetAnswer();
  } else if (parser.method == POST_METHOD) {
    return new PostAnswer();
  }
  return new InvalidAnswer();
}
