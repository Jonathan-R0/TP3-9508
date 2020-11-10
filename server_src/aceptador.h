#ifndef ACEPTADOR_H_
#define ACEPTADOR_H_

#include <list>
#include <string>

#include "../common_src/socket.h"
#include "clienthandler.h"
#include "referencefountain.h"
#include "thread.h"

typedef std::list<Clienthandler*>::iterator iterator_t;

class Aceptador : public Thread {
 private:
  Referencefountain references;
  std::list<Clienthandler*> clientlist;
  std::string rootfile;
  Socket server;

 public:
  Aceptador(char* p, const std::string& r);
  ~Aceptador();
  void removeDeadClients();
  void run() override;
};

#endif  // ACEPTADOR_H_
