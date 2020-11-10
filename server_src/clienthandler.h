#ifndef CLIENTHANDLER_H_
#define CLIENTHANDLER_H_

#include <string>

#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "referencefountain.h"

class Clienthandler : public Thread {
 private:
  const std::string& rootfile;
  bool isDeadB;
  int fd;
  Referencefountain& refs;

 public:
  Clienthandler(const std::string& file, int fdgiven, Referencefountain& r)
      : rootfile(file), isDeadB(false), fd(fdgiven), refs(r) {}
  void run() override;
  bool isDead() { return isDeadB; }
};

#endif  // CLIENTHANDLER_H_
