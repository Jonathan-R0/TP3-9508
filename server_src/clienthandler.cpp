#include "clienthandler.h"

#include <string>
#include <utility>

#include "../common_src/infomanager.h"
#include "parser.h"
#include "response.h"

Clienthandler::Clienthandler(const std::string& file, Socket s,
                             Referencefountain& r)
    : rootfile(file), isDeadB(false), refs(r) {
  self = std::move(s);
}

void Clienthandler::run() {
  Infomanager infomanager;
  std::string msg;
  infomanager.recvInfo(self, msg);
  Parser parse(rootfile);
  parse(msg);
  Response* responsegenerator = Response::create(parse);
  std::string answer =
      responsegenerator->generate(parse, refs);  // POLYMORPHISM!
  infomanager.sendInfo(self, answer);
  delete responsegenerator;
  isDeadB = true;
}
