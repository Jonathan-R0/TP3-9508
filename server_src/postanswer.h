#ifndef POSTANSWER_H_
#define POSTANWSER_H_

#include <string>

#include "../common_src/parser.h"
#include "referencefountain.h"
#include "response.h"

class PostAnswer : public Response {
 public:
  std::string generate(Parser& parser, Referencefountain& msg);
};

#endif  // POSTANSWER_H_