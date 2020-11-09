#ifndef ACEPTADOR_H_
#define ACEPTADOR_H_

#include <list>
#include <map>
#include <mutex>
#include <string>

#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "clienthandler.h"
#include "referencefountain.h"

typedef std::list<Clienthandler*>::iterator iterator_t;

class Aceptador : public Thread {
 private:
  Referencefountain references;
  std::list<Clienthandler*> clientlist;
  char* port;
  std::string rootfile;
  Socket server;

 public:
  Aceptador(char* p, std::string r);
  ~Aceptador();
  void removeDeadClients();
  void run();
};

#endif  // ACEPTADOR_H_
