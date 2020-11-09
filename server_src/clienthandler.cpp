#include "clienthandler.h"

#include <string>

#include "../common_src/infomanager.h"
#include "../common_src/parser.h"
#include "../common_src/socket.h"
#include "response.h"

void Clienthandler::run() {
  Infomanager infomanager;
  Socket self(fd);
  std::string msg;
  infomanager.recvInfo(self, msg);
  Parser parse(rootfile);
  parse(msg);

  // parse.seeStuff();

  Response* responsegenerator = Response::create(parse);
  std::string answer =
      responsegenerator->generate(parse, refs);  // POLYMORPHISM!

  infomanager.sendInfo(self, answer);
  delete responsegenerator;
  isDeadB = true;
}
