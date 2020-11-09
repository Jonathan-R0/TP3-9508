#ifndef CLIENTHANDLER_H_
#define CLIENTHANDLER_H_

#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "referencefountain.h"

class Clienthandler : public Thread {
 private:
  std::string rootfile;
  bool isDeadB;
  int fd;
  Referencefountain& refs;

 public:
  Clienthandler(std::string file, int fdgiven, Referencefountain& r)
      : rootfile(file), isDeadB(false), fd(fdgiven), refs(r) {}
  void run();
  bool isDead() { return isDeadB; }
};

#endif  // CLIENTHANDLER_H_