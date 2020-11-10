#include "clientmanager.h"

#include <iostream>

#include "../common_src/infomanager.h"
#include "../common_src/socket.h"

Clientmanager::Clientmanager(char* ip, char* port) {
  Socket toBeMoved;
  toBeMoved.connect_(port, ip);
  self = std::move(toBeMoved);
}

void Clientmanager::start() {
  Infomanager infomanager;
  infomanager.sendInfoFromStdin(self);
  std::string msg;
  infomanager.recvInfo(self, msg);
  std::cout << msg << std::endl;
}