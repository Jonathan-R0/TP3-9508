#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "../common_src/socket.h"

class Clientmanager {
 private:
  Socket self;

 public:
  Clientmanager(char* ip, char* port);
  void start();
};

#endif  // CLIENTMANAGER_H